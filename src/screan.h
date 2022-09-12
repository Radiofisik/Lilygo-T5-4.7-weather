#ifndef _screan
#define _screan

#include <Arduino.h>            // In-built
#include "epd_driver.h"         // https://github.com/Xinyuan-LilyGO/LilyGo-EPD47

#include "opensans8b.h"
#include "opensans10b.h"
#include "opensans12b.h"
#include "opensans18b.h"
#include "opensans24b.h"

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


#endif