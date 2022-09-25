// ESP32 Weather Display and a LilyGo EPD 4.7" Display, obtains Open Weather Map data, decodes and then displays it.
// This software, the ideas and concepts is Copyright (c) David Bird 2021. All rights to this software are reserved.
// #################################################################################################################

#include <Arduino.h>            // In-built
#include <esp_task_wdt.h>       // In-built
#include "freertos/FreeRTOS.h"  // In-built
#include "freertos/task.h"      // In-built
#include "epd_driver.h"         // https://github.com/Xinyuan-LilyGO/LilyGo-EPD47
#include "esp_adc_cal.h"        // In-built

#include <ArduinoJson.h>        // https://github.com/bblanchon/ArduinoJson
#include <HTTPClient.h>         // In-built

#include <PubSubClient.h>

#include <WiFi.h>               // In-built
#include <SPI.h>                // In-built
#include <time.h>               // In-built

#include "owm_credentials.h"
#include "forecast_record.h"
#include "lang.h"
#include "screen\screan.h"
#include "functions.h"
#include "weatherLoader.h"

#define autoscale_on  true
#define autoscale_off false
#define barchart_on   true
#define barchart_off  false


String  Time_str = "--:--:--";
String  Date_str = "-- --- ----";
int     wifi_signal, CurrentHour = 0, CurrentMin = 0, CurrentSec = 0, EventCnt = 0, vref = 1100;
//################ PROGRAM VARIABLES and OBJECTS ##########################################


long SleepDuration   = 30; // Sleep time in minutes, aligned to the nearest minute boundary, so if 30 will always update at 00 or 30 past the hour
int  WakeupHour      = 7;  // Wakeup after 07:00 to save battery power
int  SleepHour       = 23; // Sleep  after 23:00 to save battery power
long StartTime       = 0;
long SleepTimer      = 0;
long Delta           = 30; // ESP32 rtc speed compensation, prevents display at xx:59:yy and then xx:00:yy (one minute later) to save power


// #include "domoticz.h"
// #include "washing.h"
// #include "disher.h"

void BeginSleep() {
  epd_poweroff_all();
  UpdateLocalTime();
  SleepTimer = (SleepDuration * 60 - ((CurrentMin % SleepDuration) * 60 + CurrentSec)) + Delta; //Some ESP32 have a RTC that is too fast to maintain accurate time, so add an offset
  esp_sleep_enable_timer_wakeup(SleepTimer * 1000000LL); // in Secs, 1000000LL converts to Secs as unit = 1uSec
  Serial.println("Awake for : " + String((millis() - StartTime) / 1000.0, 3) + "-secs");
  Serial.println("Entering " + String(SleepTimer) + " (secs) of sleep time");
  Serial.println("Starting deep-sleep period...");
  esp_deep_sleep_start();  // Sleep for e.g. 30 minutes
}

boolean SetupTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer, "time.nist.gov"); //(gmtOffset_sec, daylightOffset_sec, ntpServer)
  setenv("TZ", Timezone, 1);  //setenv()adds the "TZ" variable to the environment with a value TimeZone, only used if set to 1, 0 means no change
  tzset(); // Set the TZ environment variable
  delay(100);
  return UpdateLocalTime();
}

uint8_t StartWiFi() {
  Serial.println("\r\nConnecting to: " + String(ssid));
  IPAddress dns(8, 8, 8, 8); // Use Google DNS
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    delay(500);
    WiFi.begin(ssid, password);
  }
  if (WiFi.status() == WL_CONNECTED) {
    wifi_signal = WiFi.RSSI(); // Get Wifi Signal strength now, because the WiFi will be turned off to save power!
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
  }
  else Serial.println("WiFi connection *** FAILED ***");
  return WiFi.status();
}

void StopWiFi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  Serial.println("WiFi switched Off");
}

void InitialiseSystem() {
  StartTime = millis();
  Serial.begin(115200);
  while (!Serial);
  Serial.println(String(__FILE__) + "\nStarting...");
  screanInit();
}

void loop() {
  // Nothing to do here
}

void setup() {
  int cursor_x = 200;
  int cursor_y = 500;
  InitialiseSystem();
  //epd_poweron();      // Switch on EPD display
   //writeln((GFXfont *)&OpenSans10B, "test" , &cursor_x, &cursor_y, NULL);
  //epd_clear();  
  // epd_poweroff();
  if (StartWiFi() == WL_CONNECTED && SetupTime() == true) {
    bool WakeUp = false;
    if (WakeupHour > SleepHour)
      WakeUp = (CurrentHour >= WakeupHour || CurrentHour <= SleepHour);
    else
      WakeUp = (CurrentHour >= WakeupHour && CurrentHour <= SleepHour);
    if (WakeUp) {
      
      byte Attempts = 1;
      bool RxWeather  = false;
      bool RxForecast = false;
      WiFiClient client;   // wifi client object
      // get_data_domoticz();
      //get_data_domoticz_new();
      while (RxWeather == false && Attempts <= 2) { // Try up-to 2 time for Weather and Forecast data
        RxWeather  = obtainYandexWeather(client);
        Attempts++;
      }

      Attempts = 1;
      while (RxForecast == false && Attempts <= 4) { // Try up-to 2 time for Weather and Forecast data
        if(Attempts>1){
          delay(Attempts * 200);
        }
        RxForecast = obtainWeatherData(client, "forecast");
        Attempts++;
      }
      Serial.println("Received all weather data...");
      // if --> made somes issues 
      //if (RxWeather && RxForecast)      { // Only if received both Weather or Forecast proceed
        StopWiFi();         // Reduces power consumption
        epd_poweron();      // Switch on EPD display
        epd_clear();        // Clear the screen
        DisplayWeather();   // Display the weather data
        edp_update();       // Update the display to show the information
        epd_poweroff_all(); // Switch off all power to EPD
       //}
    }
  }
  BeginSleep();
}


float SumOfPrecip(float DataArray[], int readings) {
  float sum = 0;
  for (int i = 0; i <= readings; i++) sum += DataArray[i];
  return sum;
}



void DisplayWeather() {                          // 4.7" e-paper display is 960x540 resolution
  DisplayStatusSection(600, 20, wifi_signal);    // Wi-Fi signal strength and Battery voltage
  DisplayGeneralInfoSection();                   // Top line of the display
  DisplayDisplayWindSection(137, 150, WxConditions[0].Winddir, WxConditions[0].Windspeed, 100);
  DisplayAstronomySection(5, 252);               // Astronomy section Sun rise/set, Moon phase and Moon icon
  DisplayMainWeatherSection(320, 110);           // Centre section of display for Location, temperature, Weather report, current Wx Symbol
  // DisplayWeatherIcon(835, 140);                  // Display weather icon scale = Large;

  DisplayForecastSection ( 30 , 370);              // 3hr forecast boxes
  DisplayGraphSection(320, 220);                 // Graphs of pressure, temperature, humidity and rain or snowfall
  // DisplayMQTT (260 , 245 );
}

void DisplayGeneralInfoSection() {
  setFont(OpenSans10B);
  drawString(5, 2, City, LEFT);
  setFont(OpenSans8B);
  drawString(500, 2, Date_str + "  @   " + Time_str, LEFT);
}

void DisplayWeatherIcon(int x, int y) {
  DisplayConditionsSection(x, y, WxConditions[0].Icon, LargeIcon);
}

void DisplayMainWeatherSection(int x, int y) {
  setFont(OpenSans8B);
  DisplayTempHumiPressSection(x, y - 60);
  DisplayForecastTextSection(x - 55, y + 45);
  // DisplayVisiCCoverUVISection(x - 10, y + 95);
}

void DisplayDisplayWindSection(int x, int y, float angle, float windspeed, int Cradius) {
  arrow(x, y, Cradius - 22, angle, 18, 33); // Show wind direction on outer circle of width and length
  setFont(OpenSans8B);
  int dxo, dyo, dxi, dyi;
  drawCircle(x, y, Cradius, Black);       // Draw compass circle
  drawCircle(x, y, Cradius + 1, Black);   // Draw compass circle
  drawCircle(x, y, Cradius * 0.7, Black); // Draw compass inner circle
  for (float a = 0; a < 360; a = a + 22.5) {
    dxo = Cradius * cos((a - 90) * PI / 180);
    dyo = Cradius * sin((a - 90) * PI / 180);
    if (a == 45)  drawString(dxo + x + 15, dyo + y - 18, TXT_NE, CENTER);
    if (a == 135) drawString(dxo + x + 20, dyo + y - 2,  TXT_SE, CENTER);
    if (a == 225) drawString(dxo + x - 20, dyo + y - 2,  TXT_SW, CENTER);
    if (a == 315) drawString(dxo + x - 15, dyo + y - 18, TXT_NW, CENTER);
    dxi = dxo * 0.9;
    dyi = dyo * 0.9;
    drawLine(dxo + x, dyo + y, dxi + x, dyi + y, Black);
    dxo = dxo * 0.7;
    dyo = dyo * 0.7;
    dxi = dxo * 0.9;
    dyi = dyo * 0.9;
    drawLine(dxo + x, dyo + y, dxi + x, dyi + y, Black);
  }
  drawString(x, y - Cradius - 20,     TXT_N, CENTER);
  drawString(x, y + Cradius + 10,     TXT_S, CENTER);
  drawString(x - Cradius - 15, y - 5, TXT_W, CENTER);
  drawString(x + Cradius + 10, y - 5, TXT_E, CENTER);
  drawString(x + 3, y + 50, String(angle, 0) + "°", CENTER);
  setFont(OpenSans12B);
  drawString(x, y - 50, WindDegToOrdinalDirection(angle), CENTER);
  setFont(OpenSans24B);
  drawString(x + 3, y - 18, String(windspeed, 1), CENTER);
  setFont(OpenSans12B);
  drawString(x, y + 25, (Units == "M" ? "m/s" : "mph"), CENTER);
}

String WindDegToOrdinalDirection(float winddirection) {
  if (winddirection >= 348.75 || winddirection < 11.25)  return TXT_N;
  if (winddirection >=  11.25 && winddirection < 33.75)  return TXT_NNE;
  if (winddirection >=  33.75 && winddirection < 56.25)  return TXT_NE;
  if (winddirection >=  56.25 && winddirection < 78.75)  return TXT_ENE;
  if (winddirection >=  78.75 && winddirection < 101.25) return TXT_E;
  if (winddirection >= 101.25 && winddirection < 123.75) return TXT_ESE;
  if (winddirection >= 123.75 && winddirection < 146.25) return TXT_SE;
  if (winddirection >= 146.25 && winddirection < 168.75) return TXT_SSE;
  if (winddirection >= 168.75 && winddirection < 191.25) return TXT_S;
  if (winddirection >= 191.25 && winddirection < 213.75) return TXT_SSW;
  if (winddirection >= 213.75 && winddirection < 236.25) return TXT_SW;
  if (winddirection >= 236.25 && winddirection < 258.75) return TXT_WSW;
  if (winddirection >= 258.75 && winddirection < 281.25) return TXT_W;
  if (winddirection >= 281.25 && winddirection < 303.75) return TXT_WNW;
  if (winddirection >= 303.75 && winddirection < 326.25) return TXT_NW;
  if (winddirection >= 326.25 && winddirection < 348.75) return TXT_NNW;
  return "No Data";
}

void DisplayTempHumiPressSection(int x, int y) {
  setFont(OpenSans18B);
  drawString(x - 30, y, String(WxConditions[0].Temperature, 1) + "°   " + String(WxConditions[0].Humidity, 0) + "%", LEFT);
  setFont(OpenSans12B);
  DrawPressureAndTrend(x + 195, y + 15, WxConditions[0].Pressure, WxConditions[0].Trend);
  int Yoffset = 42;
  if (WxConditions[0].Windspeed > 0) {
    drawString(x - 30, y + Yoffset, String(WxConditions[0].FeelsLike, 1) + "° FL", LEFT);   // Show FeelsLike temperature if windspeed > 0
    Yoffset += 30;
  }
  drawString(x - 30, y + Yoffset, String(WxConditions[0].High, 0) + "° | " + String(WxConditions[0].Low, 0) + "° Hi/Lo", LEFT); // Show forecast high and Low
}

void DisplayForecastTextSection(int x, int y) {
#define lineWidth 34
  setFont(OpenSans12B);
  String Wx_Description = WxConditions[0].Forecast0;
  Wx_Description.replace(".", ""); // remove any '.'
  int spaceRemaining = 0, p = 0, charCount = 0, Width = lineWidth;
  while (p < Wx_Description.length()) {
    if (Wx_Description.substring(p, p + 1) == " ") spaceRemaining = p;
    if (charCount > Width - 1) { // '~' is the end of line marker
      Wx_Description = Wx_Description.substring(0, spaceRemaining) + "~" + Wx_Description.substring(spaceRemaining + 1);
      charCount = 0;
    }
    p++;
    charCount++;
  }
  if (WxForecast[0].Rainfall > 0) Wx_Description += " (" + String(WxForecast[0].Rainfall, 1) + String((Units == "M" ? "mm" : "in")) + ")";
  String Line1 = Wx_Description.substring(0, Wx_Description.indexOf("~"));
  String Line2 = Wx_Description.substring(Wx_Description.indexOf("~") + 1);
  drawString(x + 30, y + 5, TitleCase(Line1), LEFT);
  if (Line1 != Line2) drawString(x + 30, y + 30, Line2, LEFT);
}

void DisplayVisiCCoverUVISection(int x, int y) {
  setFont(OpenSans12B);
  Serial.print("=========================="); Serial.println(WxConditions[0].Visibility);
  // Visibility(x + 5, y, String(WxConditions[0].Visibility) + "M");
  //CloudCover(x + 155, y, WxConditions[0].Cloudcover);
  CloudCover(x + 5, y, WxConditions[0].Cloudcover);
  // Display_UVIndexLevel(x + 265, y, WxConditions[0].UVI);
  Display_UVIndexLevel(x + 115, y, WxConditions[0].UVI);
}

void Display_UVIndexLevel(int x, int y, float UVI) {
  String Level = "";
  if (UVI <= 2)              Level = " (L)";
  if (UVI >= 3 && UVI <= 5)  Level = " (M)";
  if (UVI >= 6 && UVI <= 7)  Level = " (H)";
  if (UVI >= 8 && UVI <= 10) Level = " (VH)";
  if (UVI >= 11)             Level = " (EX)";
  drawString(x + 20, y - 5, String(UVI, (UVI < 0 ? 1 : 0)) + Level, LEFT);
  DrawUVI(x - 10, y - 5);
}

void DisplayForecastWeather(int x, int y, int index, int fwidth) {
  x = x + fwidth * index;
  DisplayConditionsSection(x + fwidth / 2 - 5, y + 85, WxForecast[index].Icon, SmallIcon);
  setFont(OpenSans10B);
  drawString(x + fwidth / 2, y + 30, String(ConvertUnixTime(WxForecast[index].Dt + WxConditions[0].FTimezone).substring(0, 5)), CENTER);
  drawString(x + fwidth / 2, y + 130, String(WxForecast[index].High, 0) + "°/" + String(WxForecast[index].Low, 0) + "°", CENTER);
}

double NormalizedMoonPhase(int d, int m, int y) {
  int j = JulianDate(d, m, y);
  //Calculate approximate moon phase
  double Phase = (j + 4.867) / 29.53059;
  return (Phase - (int) Phase);
}

void DisplayAstronomySection(int x, int y) {
  setFont(OpenSans10B);
  time_t now = time(NULL);
  struct tm * now_utc  = gmtime(&now);
  drawString(x + 5, y + 102, MoonPhase(now_utc->tm_mday, now_utc->tm_mon + 1, now_utc->tm_year + 1900, Hemisphere), LEFT);
  DrawMoonImage(x + 10, y + 23); // Different references!
  DrawMoon(x - 28, y - 15, 75, now_utc->tm_mday, now_utc->tm_mon + 1, now_utc->tm_year + 1900, Hemisphere); // Spaced at 1/2 moon size, so 10 - 75/2 = -28
  drawString(x + 115, y + 40, WxConditions[0].Sunrise, LEFT); // Sunrise
  drawString(x + 115, y + 80, WxConditions[0].Sunset, LEFT);  // Sunset
  DrawSunriseImage(x + 180, y + 20);
  DrawSunsetImage(x + 180, y + 60);
}

void DrawMoon(int x, int y, int diameter, int dd, int mm, int yy, String hemisphere) {
  double Phase = NormalizedMoonPhase(dd, mm, yy);
  hemisphere.toLowerCase();
  if (hemisphere == "south") Phase = 1 - Phase;
  // Draw dark part of moon
  fillCircle(x + diameter - 1, y + diameter, diameter / 2 + 1, DarkGrey);
  const int number_of_lines = 90;
  for (double Ypos = 0; Ypos <= number_of_lines / 2; Ypos++) {
    double Xpos = sqrt(number_of_lines / 2 * number_of_lines / 2 - Ypos * Ypos);
    // Determine the edges of the lighted part of the moon
    double Rpos = 2 * Xpos;
    double Xpos1, Xpos2;
    if (Phase < 0.5) {
      Xpos1 = -Xpos;
      Xpos2 = Rpos - 2 * Phase * Rpos - Xpos;
    }
    else {
      Xpos1 = Xpos;
      Xpos2 = Xpos - 2 * Phase * Rpos + Rpos;
    }
    // Draw light part of moon
    double pW1x = (Xpos1 + number_of_lines) / number_of_lines * diameter + x;
    double pW1y = (number_of_lines - Ypos)  / number_of_lines * diameter + y;
    double pW2x = (Xpos2 + number_of_lines) / number_of_lines * diameter + x;
    double pW2y = (number_of_lines - Ypos)  / number_of_lines * diameter + y;
    double pW3x = (Xpos1 + number_of_lines) / number_of_lines * diameter + x;
    double pW3y = (Ypos + number_of_lines)  / number_of_lines * diameter + y;
    double pW4x = (Xpos2 + number_of_lines) / number_of_lines * diameter + x;
    double pW4y = (Ypos + number_of_lines)  / number_of_lines * diameter + y;
    drawLine(pW1x, pW1y, pW2x, pW2y, White);
    drawLine(pW3x, pW3y, pW4x, pW4y, White);
  }
  drawCircle(x + diameter - 1, y + diameter, diameter / 2, Black);
}

void DisplayForecastSection(int x, int y) {
  int f = 0;
  do {
    DisplayForecastWeather(x, y, f, 82); // x,y cordinates, forecatsr number, spacing width
    f++;
  } while (f < 8);
}

void DisplayGraphSection(int x, int y) {
  int r = 0;
  do { // Pre-load temporary arrays with with data - because C parses by reference and remember that[1] has already been converted to I units
    if (Units == "I") pressure_readings[r] = WxForecast[r].Pressure * 0.02953;   else pressure_readings[r] = WxForecast[r].Pressure;
    if (Units == "I") rain_readings[r]     = WxForecast[r].Rainfall * 0.0393701; else rain_readings[r]     = WxForecast[r].Rainfall;
    if (Units == "I") snow_readings[r]     = WxForecast[r].Snowfall * 0.0393701; else snow_readings[r]     = WxForecast[r].Snowfall;
    temperature_readings[r]                = WxForecast[r].Temperature;
    humidity_readings[r]                   = WxForecast[r].Humidity;
    r++;
  } while (r < max_readings);
  int gwidth = 175, gheight = 100;
  int gx = (SCREEN_WIDTH - gwidth * 4) / 5 + 8;
  int gy = (SCREEN_HEIGHT - gheight - 30);
  int gap = gwidth + gx;
  // (x,y,width,height,MinValue, MaxValue, Title, Data Array, AutoScale, ChartMode)
 // DrawGraph(gx + 0 * gap, gy, gwidth, gheight, 900, 1050, Units == "M" ? TXT_PRESSURE_HPA : TXT_PRESSURE_IN, pressure_readings, max_readings, autoscale_on, barchart_off);
  //DrawGraph(gx + 1 * gap, gy, gwidth, gheight, 10, 30,    Units == "M" ? TXT_TEMPERATURE_C : TXT_TEMPERATURE_F, temperature_readings, max_readings, autoscale_on, barchart_off);
  //DrawGraph(gx + 2 * gap, gy, gwidth, gheight, 0, 100,   TXT_HUMIDITY_PERCENT, humidity_readings, max_readings, autoscale_off, barchart_off);
  if (SumOfPrecip(rain_readings, max_readings) >= SumOfPrecip(snow_readings, max_readings))
    DrawGraph(gx + 3 * gap + 5, gy, gwidth, gheight, 0, 30, Units == "M" ? TXT_RAINFALL_MM : TXT_RAINFALL_IN, rain_readings, max_readings, autoscale_on, barchart_on);
  else
    DrawGraph(gx + 3 * gap + 5, gy, gwidth, gheight, 0, 30, Units == "M" ? TXT_SNOWFALL_MM : TXT_SNOWFALL_IN, snow_readings, max_readings, autoscale_on, barchart_on);
}

void DisplayConditionsSection(int x, int y, String IconName, bool IconSize) {
  Serial.println("Icon name: " + IconName);
  if      (IconName == "01d" || IconName == "01n") ClearSky(x, y, IconSize, IconName);
  else if (IconName == "02d" || IconName == "02n") FewClouds(x, y, IconSize, IconName);
  else if (IconName == "03d" || IconName == "03n") ScatteredClouds(x, y, IconSize, IconName);
  else if (IconName == "04d" || IconName == "04n") BrokenClouds(x, y, IconSize, IconName);
  else if (IconName == "09d" || IconName == "09n") ChanceRain(x, y, IconSize, IconName);
  else if (IconName == "10d" || IconName == "10n") Rain(x, y, IconSize, IconName);
  else if (IconName == "11d" || IconName == "11n") Thunderstorms(x, y, IconSize, IconName);
  else if (IconName == "13d" || IconName == "13n") Snow(x, y, IconSize, IconName);
  else if (IconName == "50d" || IconName == "50n") Mist(x, y, IconSize, IconName);
  else                                             Nodata(x, y, IconSize, IconName);
}

void DrawPressureAndTrend(int x, int y, float pressure, String slope) {
  drawString(x + 25, y - 10, String(pressure, (Units == "M" ? 0 : 1)) + (Units == "M" ? "mmHg" : "in"), LEFT);
  if      (slope == "+") {
    DrawSegment(x, y, 0, 0, 8, -8, 8, -8, 16, 0);
    DrawSegment(x - 1, y, 0, 0, 8, -8, 8, -8, 16, 0);
  }
  else if (slope == "0") {
    DrawSegment(x, y, 8, -8, 16, 0, 8, 8, 16, 0);
    DrawSegment(x - 1, y, 8, -8, 16, 0, 8, 8, 16, 0);
  }
  else if (slope == "-") {
    DrawSegment(x, y, 0, 0, 8, 8, 8, 8, 16, 0);
    DrawSegment(x - 1, y, 0, 0, 8, 8, 8, 8, 16, 0);
  }
}

void DisplayStatusSection(int x, int y, int rssi) {
  setFont(OpenSans8B);
  DrawRSSI(x + 305, y + 15, rssi);
  DrawBattery(x + 150, y);
}

void DrawRSSI(int x, int y, int rssi) {
  int WIFIsignal = 0;
  int xpos = 1;
  for (int _rssi = -100; _rssi <= rssi; _rssi = _rssi + 20) {
    if (_rssi <= -20)  WIFIsignal = 30; //            <-20dbm displays 5-bars
    if (_rssi <= -40)  WIFIsignal = 24; //  -40dbm to  -21dbm displays 4-bars
    if (_rssi <= -60)  WIFIsignal = 18; //  -60dbm to  -41dbm displays 3-bars
    if (_rssi <= -80)  WIFIsignal = 12; //  -80dbm to  -61dbm displays 2-bars
    if (_rssi <= -100) WIFIsignal = 6;  // -100dbm to  -81dbm displays 1-bar
    fillRect(x + xpos * 8, y - WIFIsignal, 6, WIFIsignal, Black);
    xpos++;
  }
}

boolean UpdateLocalTime() {
  struct tm timeinfo;
  char   time_output[30], day_output[30], update_time[30];
  while (!getLocalTime(&timeinfo, 5000)) { // Wait for 5-sec for time to synchronise
    Serial.println("Failed to obtain time");
    return false;
  }
  CurrentHour = timeinfo.tm_hour;
  CurrentMin  = timeinfo.tm_min;
  CurrentSec  = timeinfo.tm_sec;
  //See http://www.cplusplus.com/reference/ctime/strftime/
  Serial.println(&timeinfo, "%a %b %d %Y   %H:%M:%S");      // Displays: Saturday, June 24 2017 14:05:49
  if (Units == "M") {
    sprintf(day_output, "%s, %02u %s %04u", weekday_D[timeinfo.tm_wday], timeinfo.tm_mday, month_M[timeinfo.tm_mon], (timeinfo.tm_year) + 1900);
    strftime(update_time, sizeof(update_time), "%H:%M:%S", &timeinfo);  // Creates: '@ 14:05:49'   and change from 30 to 8 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    sprintf(time_output, "%s", update_time);
  }
  else
  {
    strftime(day_output, sizeof(day_output), "%a %b-%d-%Y", &timeinfo); // Creates  'Sat May-31-2019'
    strftime(update_time, sizeof(update_time), "%r", &timeinfo);        // Creates: '@ 02:05:49pm'
    sprintf(time_output, "%s", update_time);
  }
  Date_str = day_output;
  Time_str = time_output;
  return true;
}

void DrawBattery(int x, int y) {
  uint8_t percentage = 100;
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
    vref = adc_chars.vref;
  }
  float voltage = analogRead(36) / 4096.0 * 6.566 * (vref / 1000.0);
  if (voltage > 1 ) { // Only display if there is a valid reading
    Serial.println("\nVoltage = " + String(voltage));
    percentage = 2836.9625 * pow(voltage, 4) - 43987.4889 * pow(voltage, 3) + 255233.8134 * pow(voltage, 2) - 656689.7123 * voltage + 632041.7303;
    if (voltage >= 4.20) percentage = 100;
    if (voltage <= 3.20) percentage = 0;  // orig 3.5
    drawRect(x + 25, y - 14, 40, 15, Black);
    fillRect(x + 65, y - 10, 4, 7, Black);
    fillRect(x + 27, y - 12, 36 * percentage / 100.0, 11, Black);
    drawString(x + 85, y - 14, String(percentage) + "%  " + String(voltage, 1) + "v", LEFT);
  }
}

void DrawUVI(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = uvi_width, .height = uvi_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) uvi_data);
}
/*
void DrawDimmerImage(int x, int y) {
  drawString(x + 30, y, String(CloudCover) + "%", LEFT);
}

void DrawDisherImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = disher_width, .height =  disher_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) disher_data);
}

void DrawLinkyImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = linky_width, .height =  linky_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) linky_data);
}

void DrawSolarImage(int x, int y) {
  Rect_t area = {
    .x = x, .y = y, .width  = solar_width, .height =  solar_height
  };
  epd_draw_grayscale_image(area, (uint8_t *) solar_data);
}
*/


/////////////////// code domotique  //////////////////////////////////////////////////////////////
// /// reste du code de traitement dans domoticz.h 
// void DisplayMQTT(int x, int y) {
// drawRect ( x-10, y-10 , 700,145, 0x65 )   ;
// setFont(OpenSans12B);

// for (int j = 0; j <= 3 ; j++) {
//     int cy = 0 ;
// for (int i = j*3; i <= (j*3 + 2) ; i++) { 
//     if  ( domoticz_IDX[i][0] != NULL ) {  // prevent hang null value
//       int ycorrect=0;
//     if ( domoticz_IDX[i][0].indexOf("y") != -1  ||domoticz_IDX[i][0].indexOf("p") != -1 ) ycorrect = -6 ;   /// correction du big polices  ( 12b) 
//     drawString(x +10+ cy*225 , y+(j*35)+ycorrect , domoticz_IDX[i][0] +" : " + domoticz_result[i],  LEFT);
//     cy++; 
//     }
// }}
// /// condition d'affichage des images 
// if ( domoticz_result[0].substring(0,2).toInt() > wash ) { DrawWashingImage ( x+500 , y+ 35 );  }// si temp eau > 45 > ok pour machine laver
// if ( domoticz_result[4].substring(0,4).toInt() > disher ) DrawDisherImage ( x+575  , y+ 35 ); // si prod > 700w alors ok pour lave vaisselle
//   }

// void DrawWashingImage(int x, int y) {
//   Rect_t area = {
//     .x = x, .y = y, .width  = washing_width, .height =  washing_height
//   };
//   epd_draw_grayscale_image(area, (uint8_t *) washing_data);
// }

// void DrawDisherImage(int x, int y) {
//   Rect_t area = {
//     .x = x, .y = y, .width  = disher_width, .height =  disher_height
//   };
//   epd_draw_grayscale_image(area, (uint8_t *) disher_data);
// }

//////////////////////////// fin code domotique  //////////////////////////////////////////////////////////////

/*
   1071 lines of code 03-03-2021
*/
