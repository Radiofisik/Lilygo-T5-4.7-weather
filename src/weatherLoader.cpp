#include "weatherLoader.h"
#include "owm_credentials.h"

float pressure_readings[max_readings]    = {0};
float temperature_readings[max_readings] = {0};
float humidity_readings[max_readings]    = {0};
float rain_readings[max_readings]        = {0};
float snow_readings[max_readings]        = {0};

Forecast_record_type  WxConditions[1];
Forecast_record_type  WxForecast[max_readings];

void Convert_Readings_to_Imperial() { // Only the first 3-hours are used
  WxConditions[0].Pressure = hPa_to_inHg(WxConditions[0].Pressure);
  WxForecast[0].Rainfall   = mm_to_inches(WxForecast[0].Rainfall);
  WxForecast[0].Snowfall   = mm_to_inches(WxForecast[0].Snowfall);
}

float dirToDeg(String dir){

// «nw» — северо-западное.
 if(dir == "n")
    return 315;

// «n» — северное.
 if(dir == "n")
    return 0;

// «ne» — северо-восточное.
 if(dir == "ne")
    return 45;

// «e» — восточное.
 if(dir == "e")
    return 90;

// «se» — юго-восточное.
 if(dir == "se")
    return 135;

// «s» — южное.
 if(dir == "s")
    return 180;

// «sw» — юго-западное.
 if(dir == "sw")
    return 270;

// «w» — западное.
 if(dir == "w")
    return 270;

// «с» — штиль.
    return 0;
}

bool DecodeWeather(WiFiClient& json, String Type) {
  Serial.print(F("\nCreating object...and "));
  DynamicJsonDocument doc(64 * 1024);                      // allocate the JsonDocument
  DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document
  if (error) {                                             // Test if parsing succeeds.
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }
  // convert it to a JsonObject
  JsonObject root = doc.as<JsonObject>();
  Serial.println(" Decoding " + Type + " data");
  if (Type == "onecall") {
    // All Serial.println statements are for diagnostic purposes and some are not required, remove if not needed with //
    WxConditions[0].High        = -50; // Minimum forecast low
    WxConditions[0].Low         = 50;  // Maximum Forecast High
    WxConditions[0].FTimezone   = doc["timezone_offset"]; // "0"
    JsonObject current = doc["current"];
    // WxConditions[0].Sunrise     = current["sunrise"];                              Serial.println("SRis: " + String(WxConditions[0].Sunrise));
    // WxConditions[0].Sunset      = current["sunset"];                               Serial.println("SSet: " + String(WxConditions[0].Sunset));
    WxConditions[0].Temperature = current["temp"];                                 Serial.println("Temp: " + String(WxConditions[0].Temperature));
    WxConditions[0].FeelsLike   = current["feels_like"];                           Serial.println("FLik: " + String(WxConditions[0].FeelsLike));
    WxConditions[0].Pressure    = current["pressure"];                             Serial.println("Pres: " + String(WxConditions[0].Pressure));
    WxConditions[0].Humidity    = current["humidity"];                             Serial.println("Humi: " + String(WxConditions[0].Humidity));
    WxConditions[0].DewPoint    = current["dew_point"];                            Serial.println("DPoi: " + String(WxConditions[0].DewPoint));
    WxConditions[0].UVI         = current["uvi"];                                  Serial.println("UVin: " + String(WxConditions[0].UVI));
    WxConditions[0].Cloudcover  = current["clouds"];                               Serial.println("CCov: " + String(WxConditions[0].Cloudcover));
    WxConditions[0].Visibility  = current["visibility"];                           Serial.println("Visi: " + String(WxConditions[0].Visibility));
    WxConditions[0].Windspeed   = current["wind_speed"];                           Serial.println("WSpd: " + String(WxConditions[0].Windspeed));
    WxConditions[0].Winddir     = current["wind_deg"];                             Serial.println("WDir: " + String(WxConditions[0].Winddir));
    JsonObject current_weather  = current["weather"][0];
    String Description = current_weather["description"];                           // "scattered clouds"
    String Icon        = current_weather["icon"];                                  // "01n"
    WxConditions[0].Forecast0   = Description;                                     Serial.println("Fore: " + String(WxConditions[0].Forecast0));
    WxConditions[0].Icon        = Icon;                                            Serial.println("Icon: " + String(WxConditions[0].Icon));
  }
  if (Type == "forecast") {
    //Serial.println(json);
    Serial.print(F("\nReceiving Forecast period - ")); //------------------------------------------------
    JsonArray list                    = root["list"];
    for (byte r = 0; r < max_readings; r++) {
      Serial.println("\nPeriod-" + String(r) + "--------------");
      WxForecast[r].Dt                = list[r]["dt"].as<int>();
      WxForecast[r].Temperature       = list[r]["main"]["temp"].as<float>();       Serial.println("Temp: " + String(WxForecast[r].Temperature));
      WxForecast[r].Low               = list[r]["main"]["temp_min"].as<float>();   Serial.println("TLow: " + String(WxForecast[r].Low));
      WxForecast[r].High              = list[r]["main"]["temp_max"].as<float>();   Serial.println("THig: " + String(WxForecast[r].High));
      WxForecast[r].Pressure          = list[r]["main"]["pressure"].as<float>();   Serial.println("Pres: " + String(WxForecast[r].Pressure));
      WxForecast[r].Humidity          = list[r]["main"]["humidity"].as<float>();   Serial.println("Humi: " + String(WxForecast[r].Humidity));
      WxForecast[r].Icon              = list[r]["weather"][0]["icon"].as<char*>(); Serial.println("Icon: " + String(WxForecast[r].Icon));
      WxForecast[r].Rainfall          = list[r]["rain"]["3h"].as<float>();         Serial.println("Rain: " + String(WxForecast[r].Rainfall));
      WxForecast[r].Snowfall          = list[r]["snow"]["3h"].as<float>();         Serial.println("Snow: " + String(WxForecast[r].Snowfall));
      if (r < 8) { // Check next 3 x 8 Hours = 1 day
        if (WxForecast[r].High > WxConditions[0].High) WxConditions[0].High = WxForecast[r].High; // Get Highest temperature for next 24Hrs
        if (WxForecast[r].Low  < WxConditions[0].Low)  WxConditions[0].Low  = WxForecast[r].Low;  // Get Lowest  temperature for next 24Hrs
      }
    }
    //------------------------------------------
    float pressure_trend = WxForecast[0].Pressure - WxForecast[2].Pressure; // Measure pressure slope between ~now and later
    pressure_trend = ((int)(pressure_trend * 10)) / 10.0; // Remove any small variations less than 0.1
    WxConditions[0].Trend = "=";
    if (pressure_trend > 0)  WxConditions[0].Trend = "+";
    if (pressure_trend < 0)  WxConditions[0].Trend = "-";
    if (pressure_trend == 0) WxConditions[0].Trend = "0";

    if (Units == "I") Convert_Readings_to_Imperial();
  }
  return true;
}
//#########################################################################################

//#########################################################################################
bool obtainWeatherData(WiFiClient & client, const String & RequestType) {
  const String units = (Units == "M" ? "metric" : "imperial");
  client.stop(); // close connection before sending a new request
  HTTPClient http;
  //api.openweathermap.org/data/2.5/RequestType?lat={lat}&lon={lon}&appid={API key}
  String uri = "/data/2.5/" + RequestType + "?lat=" + Latitude + "&lon=" + Longitude + "&appid=" + apikey + "&mode=json&units=" + units + "&lang=" + Language;
  if (RequestType == "onecall") uri += "&exclude=minutely,hourly,alerts,daily";
  http.begin(client, server, 80, uri); //http.begin(uri,test_root_ca); //HTTPS example connection
  int httpCode = http.GET();
  
  // Serial.print(uri);
  Serial.printf("http request done with code %d", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    if (!DecodeWeather(http.getStream(), RequestType)) return false;
    client.stop();
  }
  else
  {
    Serial.printf("connection failed, error: %s", http.errorToString(httpCode).c_str());
    client.stop();
    http.end();
    return false;
  }
  http.end();
  return true;
}



bool DecodeYaWeather(WiFiClient& json) {
  Serial.print(F("\nCreating ya object...and "));
  DynamicJsonDocument doc(64 * 1024);                      // allocate the JsonDocument
  DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document
  if (error) {                                             // Test if parsing succeeds.
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }
  // convert it to a JsonObject
  JsonObject root = doc.as<JsonObject>();
    // All Serial.println statements are for diagnostic purposes and some are not required, remove if not needed with //
    WxConditions[0].High        = -50; // Minimum forecast low
    WxConditions[0].Low         = 50;  // Maximum Forecast High
    WxConditions[0].FTimezone  = 0;//= doc["timezone_offset"]; // "0"
    JsonObject fact = doc["fact"];
    JsonObject forecast = doc["forecast"];

    String sunrise = forecast["sunrise"];
    String sunset = forecast["sunset"];
    WxConditions[0].Sunrise     = sunrise;                               Serial.println("SRis: " + String(WxConditions[0].Sunrise));
    WxConditions[0].Sunset      = sunset;                               Serial.println("SSet: " + String(WxConditions[0].Sunset));
    WxConditions[0].Temperature = fact["temp"];                                 Serial.println("Temp: " + String(WxConditions[0].Temperature));
    WxConditions[0].FeelsLike   = fact["feels_like"];                           Serial.println("FLik: " + String(WxConditions[0].FeelsLike));
    WxConditions[0].Pressure    = fact["pressure_mm"];                             Serial.println("Pres: " + String(WxConditions[0].Pressure));
    WxConditions[0].Humidity    = fact["humidity"];                             Serial.println("Humi: " + String(WxConditions[0].Humidity));
    WxConditions[0].DewPoint    = 0;// current["dew_point"];                            Serial.println("DPoi: " + String(WxConditions[0].DewPoint));
    WxConditions[0].UVI         = 0; //current["uvi"];                                  Serial.println("UVin: " + String(WxConditions[0].UVI));
    // WxConditions[0].Cloudcover  = current["clouds"];                               Serial.println("CCov: " + String(WxConditions[0].Cloudcover));
    // WxConditions[0].Visibility  = current["visibility"];                           Serial.println("Visi: " + String(WxConditions[0].Visibility));
    WxConditions[0].Windspeed   = fact["wind_speed"];                           Serial.println("WSpd: " + String(WxConditions[0].Windspeed));
    WxConditions[0].Winddir     = dirToDeg(fact["wind_dir"]);                             Serial.println("WDir: " + String(WxConditions[0].Winddir));
    // JsonObject current_weather  = current["weather"][0];
    String Description = fact["condition"];                           // "scattered clouds"
    String Icon        = fact["icon"];                                  // "01n"
    WxConditions[0].Forecast0   = Description;                                     Serial.println("Fore: " + String(WxConditions[0].Forecast0));
    WxConditions[0].Icon        = Icon;                                            Serial.println("Icon: " + String(WxConditions[0].Icon));
  
  return true;
}


bool obtainYandexWeather(WiFiClient & client){
  client.stop(); // close connection before sending a new request
  HTTPClient http;
  String uri = "/v2/informers?lat=" + Latitude + "&lon=" + Longitude + "&lang=en_US";// + Language;
  Serial.println(uri);

  http.begin(client, yaServer, 80, uri); //http.begin(uri,test_root_ca); //HTTPS example connection
  http.addHeader("X-Yandex-API-Key", yaApikey);
  int httpCode = http.GET();
  
  // Serial.print(uri);
  Serial.printf("http request to yandex done with code %d", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    if (!DecodeYaWeather(http.getStream())) return false;
    client.stop();
  }
  else
  {
    Serial.printf("connection failed, error: %s", http.errorToString(httpCode).c_str());
    client.stop();
    http.end();
    return false;
  }
  http.end();
  return true;
}