#include "wifiScanner.h"
#include "tftScreen.h"

int wifiScan(Adafruit_ILI9341 &tft)
{
  tft.begin();
  tft.setRotation(1);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Connecting to WiFi");
  n = WiFi.scanNetworks();
  
  //int x = WiFi.scanComplete();
  Serial.println("Scan started");
  tft.println("Scan started");
  delay(500);

  clearScreen(tft);

  if(n == 0)
  {
    Serial.println("Not networks found");
    tft.println("Not networks found");
  }
  else
  {
    
    if(n > MAXLINE)
    {
      screenScroll(tft, n);
    }
    else{
      screenShow(tft, n);
    }
  }
  
  Serial.println("Enter the no. of the network you want to connect");
  while (Serial.available() == 0){}
  int no_ssid = Serial.parseInt();
  
  wifiConnection(tft, no_ssid);

  return n;
}

int wifiInit(Adafruit_ILI9341 &tft, unsigned long &timeout, int &trial)
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
    return WiFi.status();
}

void wifiConnection(Adafruit_ILI9341 &tft, int no_ssid)
{
    ssid = WiFi.SSID(no_ssid - 1);  
  
    if((WiFi.encryptionType(no_ssid - 1) != WIFI_AUTH_OPEN))
    {
        clearScreen(tft);
        tft.setTextColor(ILI9341_GREEN);
        tft.print(no_ssid);
        tft.print(": ");
        tft.print(WiFi.SSID(no_ssid - 1));
        tft.print(" (");
        tft.print(WiFi.RSSI(no_ssid - 1));
        tft.print(")");
        if((WiFi.encryptionType(no_ssid - 1) == WIFI_AUTH_OPEN)) tft.println("*");
        tft.setTextColor(ILI9341_BLUE);
        tft.println("Please enter the password of the network you chose");
        Serial.println("Please enter the password of the network you chose");
        while (Serial.available() == 0){}
        pass = Serial.readString();
        for(int i = 0; i < pass.length(); i++) tft.print("*");
        tft.println();
    }
    else
    {
        pass = "";
    }
}