#ifndef _screan
#define _screan

#include <Arduino.h>            // In-built
#include "epd_driver.h"         // https://github.com/Xinyuan-LilyGO/LilyGo-EPD47

#include "opensans8b.h"
#include "opensans10b.h"
#include "opensans12b.h"
#include "opensans18b.h"
#include "opensans24b.h"

//fonts
#include "moon.h"
#include "sunrise.h"
#include "sunset.h"
#include "uvi.h"

const boolean LargeIcon   = true;
const boolean SmallIcon   = false;

#define SCREEN_WIDTH   EPD_WIDTH
#define SCREEN_HEIGHT  EPD_HEIGHT

enum alignment {LEFT, RIGHT, CENTER};
#define White         0xFF
#define LightGrey     0xBB
#define Grey          0x88
#define DarkGrey      0x44
#define Black         0x00

extern GFXfont  currentFont;
extern uint8_t *framebuffer;

void screanInit();

void DrawGraph(int x_pos, int y_pos, int gwidth, int gheight, float Y1Min, float Y1Max, String title, float DataArray[], int readings, boolean auto_scale, boolean barchart_mode);

void drawString(int x, int y, String text, alignment align);

void fillCircle(int x, int y, int r, uint8_t color);

void drawFastHLine(int16_t x0, int16_t y0, int length, uint16_t color);

void drawFastVLine(int16_t x0, int16_t y0, int length, uint16_t color);

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void drawCircle(int x0, int y0, int r, uint8_t color);

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                  int16_t x2, int16_t y2, uint16_t color);

void drawPixel(int x, int y, uint8_t color);

void setFont(GFXfont const & font);

void edp_update();


// Symbols are drawn on a relative 10x10grid and 1 scale unit = 1 drawing unit
void addcloud(int x, int y, int scale, int linesize) ;
void addrain(int x, int y, int scale, bool IconSize) ;
void addsnow(int x, int y, int scale, bool IconSize);
void addtstorm(int x, int y, int scale);
void addsun(int x, int y, int scale, bool IconSize);
void addfog(int x, int y, int scale, int linesize, bool IconSize);

void DrawAngledLine(int x, int y, int x1, int y1, int size, int color);
void ClearSky(int x, int y, bool IconSize, String IconName);
void BrokenClouds(int x, int y, bool IconSize, String IconName);
void FewClouds(int x, int y, bool IconSize, String IconName);
void ScatteredClouds(int x, int y, bool IconSize, String IconName);
void Rain(int x, int y, bool IconSize, String IconName);
void ChanceRain(int x, int y, bool IconSize, String IconName);
void Thunderstorms(int x, int y, bool IconSize, String IconName);
void Snow(int x, int y, bool IconSize, String IconName);
void Mist(int x, int y, bool IconSize, String IconName);
void CloudCover(int x, int y, int CloudCover);
void Visibility(int x, int y, String Visibility);

void addmoon(int x, int y, bool IconSize);

void Nodata(int x, int y, bool IconSize, String IconName);

void DrawMoonImage(int x, int y);
void DrawSunriseImage(int x, int y);
void DrawSunsetImage(int x, int y);

void arrow(int x, int y, int asize, float aangle, int pwidth, int plength);
void DrawSegment(int x, int y, int o1, int o2, int o3, int o4, int o11, int o12, int o13, int o14);

#endif