#pragma once
#include <Arduino.h>

float mm_to_inches(float value_mm) ;
float hPa_to_inHg(float value_hPa);
int JulianDate(int d, int m, int y);
String TitleCase(String text);
String MoonPhase(int d, int m, int y, String hemisphere);
String ConvertUnixTime(int unix_time);