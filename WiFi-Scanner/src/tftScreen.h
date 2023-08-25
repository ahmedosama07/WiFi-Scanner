#ifndef tftScreen_h
#define tftScreen_h
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <WiFi.h>

#ifndef MAXLINE
#define MAXLINE 12
#endif

#ifndef DOWNBTN
#define DOWNBTN 5
#endif

#ifndef UPBTN
#define UPBTN 22
#endif

/**
*   Functions used in wifiScanner
*   - clearScreenclearScreen(Adafruit_ILI9341 &tft)
*   - screenScroll(Adafruit_ILI9341 &tft, int n)
*   - screenShow(Adafruit_ILI9341 &tft, int n)
**/
void clearScreen(Adafruit_ILI9341 &tft);
void screenScroll(Adafruit_ILI9341 &tft, int n);
void screenShow(Adafruit_ILI9341 &tft, int n);
void screenShowOnce(Adafruit_ILI9341 &tft, int i);
void showHeader(Adafruit_ILI9341 &tft, int n);
void showTrailer(Adafruit_ILI9341 &tft);

#endif