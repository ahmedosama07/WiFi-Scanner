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
    int j = 1;
    if(n > MAXLINE)
    {
      int line = 0;
      
      clearScreen(tft);

      tft.setTextColor(ILI9341_GREEN);
      tft.print(n);
      tft.println(" networks found");
      tft.setTextColor(ILI9341_BLUE);
      for(int i = 0; i < n; i++)
      {
        line++;
        tft.print(i + 1);
        tft.print(": ");
        tft.print(WiFi.SSID(i));
        tft.print(" (");
        tft.print(WiFi.RSSI(i));
        tft.print(")");
        if((WiFi.encryptionType(i) == WIFI_AUTH_OPEN))
        {
          Serial.println("*");
          tft.println("*");
        }
        delay(10);
        Serial.println("");
        if(line >= MAXLINE) break;
      }
      tft.println("Enter the no. of the network you want to connect");
      int endScroll = 0;
      int selected = 0;
      while(!endScroll && !selected)
      {
        if(digitalRead(downBtn) == LOW)
        {
          clearScreen(tft);
          tft.setTextColor(ILI9341_GREEN);
          tft.print(n);
          tft.println(" networks found");
          tft.setTextColor(ILI9341_BLUE);
          line = 0;
          for(int i = j; i < n; i++)
          {
            line++;
            tft.print(i + 1);
            tft.print(": ");
            tft.print(WiFi.SSID(i));
            tft.print(" (");
            tft.print(WiFi.RSSI(i));
            tft.print(")");
            if((WiFi.encryptionType(i) == WIFI_AUTH_OPEN))
            {
              Serial.println("*");
              tft.println("*");
            }
            delay(10);
            Serial.println("");
            if(line >= MAXLINE) break;
          }
          tft.println("Enter the no. of the network you want to connect");
          j++;
          Serial.println(j);
          if(j == n-10) endScroll = 1;
          if(Serial.available()) selected = 1;
        }
      }
      
    }
    else{
      Serial.print(n);
      Serial.println(" networks found");
      tft.setTextColor(ILI9341_GREEN);
      tft.print(n);
      tft.println(" networks found");

      tft.setTextColor(ILI9341_BLUE);
      for(int i = 0; i < n; i++)
      {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");

        tft.print(i + 1);
        tft.print(": ");
        tft.print(WiFi.SSID(i));
        tft.print(" (");
        tft.print(WiFi.RSSI(i));
        tft.print(")");
        if((WiFi.encryptionType(i) == WIFI_AUTH_OPEN))
        {
          Serial.println("*");
          tft.println("*");
        }
        delay(10);
        Serial.println("");
      }
    }
  }
  
  Serial.println("Enter the no. of the network you want to connect");
  while (Serial.available() == 0){}
  int no_ssid = Serial.parseInt();
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