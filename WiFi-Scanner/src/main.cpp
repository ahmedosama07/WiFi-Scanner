#include "wifiScanner.h"
#include "tftScreen.h"



unsigned long timestart = 0;
unsigned long timeout=0;


int trial = 0;

#define DOWNBTN 5

#define TFT_DC 2
#define TFT_CS 15

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() {
  pinMode(DOWNBTN, INPUT_PULLUP);

  Serial.begin(115200);
  

  wifiScan(tft);
  wifiInit(tft, timeout, trial);

  tft.print("\nOK! IP=");
  tft.println(WiFi.localIP());
}

void loop() {
  if(trial > 3)
  {
    wifiScan(tft);
    wifiInit(tft, timeout, trial);
  }
  else
  {
    if((millis() - timestart > 2000) && (WiFi.status()  != WL_CONNECTED))
    {
      Serial.println("Reconnecting to Wifi...");
      WiFi.disconnect();
      wifiInit(tft, timeout, trial);
      trial++;
      WiFi.reconnect();
      timestart=millis();
    }
  }
}