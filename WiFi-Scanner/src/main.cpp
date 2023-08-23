#include <WiFi.h>
#include "tftScreen.h"

String ssid = "";
String pass = "";

unsigned long timestart = 0;
unsigned long timeout=0;


int trial = 0;

#define DOWNBTN 5

#define TFT_DC 2
#define TFT_CS 15

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);



void wifi_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  clearScreen(tft);

  tft.setTextColor(ILI9341_WHITE);

  Serial.print("Connecting to Wifi...");
  tft.print("Connecting to Wifi...");
  timeout = millis();
  while((WiFi.status() != WL_CONNECTED) && (millis() - timeout < 8000))
  {
    Serial.print(".");
    delay(1000);
  }


  clearScreen(tft);
  

  if(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_NO_SSID_AVAIL)
  {
    Serial.println("Password is not correct");
    tft.setTextColor(ILI9341_RED);
    tft.println("Password is not correct");
  }
  else if(WiFi.status() != WL_CONNECTED && WiFi.status() == WL_NO_SSID_AVAIL)
  {
    Serial.println("Wifi network is not avaliable");
    tft.setTextColor(ILI9341_RED);
    tft.println("Wifi network is not avaliable");
  }
  else
  {
    Serial.println("");
    Serial.println("Connected successfully");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
    tft.setTextColor(ILI9341_WHITE);
    tft.println("");
    tft.println("Connected successfully");
    tft.print("IP Address : ");
    tft.println(WiFi.localIP());
    trial = 0;
  }
  
}

void setup() {
  pinMode(DOWNBTN, INPUT_PULLUP);

  Serial.begin(115200);
  

  wifiScan();
  wifiInit();

  tft.print("\nOK! IP=");
  tft.println(WiFi.localIP());
}

void loop() {
  if(trial > 3)
  {
    wifi_scan();
    wifi_init();
  }
  else
  {
    if((millis() - timestart > 2000) && (WiFi.status()  != WL_CONNECTED))
    {
      Serial.println("Reconnecting to Wifi...");
      WiFi.disconnect();
      wifi_init();
      trial++;
      WiFi.reconnect();
      timestart=millis();
    }
  }
}