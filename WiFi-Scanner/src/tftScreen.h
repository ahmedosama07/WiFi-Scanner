#ifndef tftScreen_h
#define tftScreen_h
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <WiFi.h>

#ifndef MAXLINE
#define MAXLINE 11
#endif

#ifndef DOWNBTN
#define DOWNBTN 5
#endif

void clearScreen(Adafruit_ILI9341 &tft);
void screenScroll(Adafruit_ILI9341 &tft, int n);
void screenShow(Adafruit_ILI9341 &tft, int n);
void screenShowOnce(Adafruit_ILI9341 &tft, int i);

#endif