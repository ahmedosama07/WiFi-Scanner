#include "tftScreen.h"

void clearScreen(Adafruit_ILI9341 &tft)
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
}

void screenScroll(Adafruit_ILI9341 &tft, int n)
{
    int j = 1;
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
        if(digitalRead(DOWNBTN) == LOW)
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
            screenShowOnce(tft, i);
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

void screenShow(Adafruit_ILI9341 &tft, int n)
{
  Serial.print(n);
  Serial.println(" networks found");
  tft.setTextColor(ILI9341_GREEN);
  tft.print(n);
  tft.println(" networks found");

  tft.setTextColor(ILI9341_BLUE);
  for(int i = 0; i < n; i++)
  {
    screenShowOnce(tft, i);
  }
}

void screenShowOnce(Adafruit_ILI9341 &tft, int i)
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