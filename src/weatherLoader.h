#pragma once
#include <WiFi.h>
#include <ArduinoJson.h>        // https://github.com/bblanchon/ArduinoJson
#include <HTTPClient.h>         // In-built
#include "lang.h"
#include "forecast_record.h"
#include "functions.h"


#define max_readings 24 // Limited to 3-days here, but could go to 5-days = 40 as the data is issued  

extern Forecast_record_type  WxConditions[1];
extern Forecast_record_type  WxForecast[max_readings];

extern float pressure_readings[max_readings] ;
extern float temperature_readings[max_readings];
extern float humidity_readings[max_readings];
extern float rain_readings[max_readings];
extern float snow_readings[max_readings];

bool DecodeWeather(WiFiClient& json, String Type) ;
bool obtainWeatherData(WiFiClient & client, const String & RequestType);
bool obtainYandexWeather(WiFiClient & client);