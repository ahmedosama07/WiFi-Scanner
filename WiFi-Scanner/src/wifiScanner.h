#include <WiFi.h>

int n = 0;
String ssid = "";
String pass = "";

int wifiScan(Adafruit_ILI9341 &tft);
int wifiInit(Adafruit_ILI9341 &tft, unsigned long &timeout, int &trial);
void wifiConnection(Adafruit_ILI9341 &tft, int no_ssid);