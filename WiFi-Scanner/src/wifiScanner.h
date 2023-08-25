#ifndef WIFISCANNER_H
#define WIFISCANNER_H
#include <WiFi.h>
#include "tftScreen.h"

extern int n;
extern String ssid;
extern  String pass;

int wifiScan(Adafruit_ILI9341 &tft);
int wifiInit(Adafruit_ILI9341 &tft, unsigned long &timeout, int &trial);
void wifiConnection(Adafruit_ILI9341 &tft, int no_ssid);
String getWiFiStatus(int Status);

#endif