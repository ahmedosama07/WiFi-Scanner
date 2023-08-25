#include "tftScreen.h"

void clearScreen(Adafruit_ILI9341 &tft)
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
}

void screenScroll(Adafruit_ILI9341 &tft, int n)
{
    int j = 0;
    int line = 0;
      
    clearScreen(tft);

    showHeader(tft, n);

    for(int i = 0; i < n; i++)
    {
    line++;
    screenShowOnce(tft, i);
    if(line >= MAXLINE) break;
    tft.println("   |                         |      |    |           ");
    }
    showTrailer(tft);
    int endScroll = 0;
    int selected = 0;
    scroll :
    while(!endScroll && !selected)
      {
        if(digitalRead(DOWNBTN) == LOW)
        {
          j++;
          clearScreen(tft);
          showHeader(tft, n);
          tft.setTextColor(ILI9341_WHITE);
          line = 0;
          for(int i = j; i < n; i++)
          {
            line++;
            screenShowOnce(tft, i);
            if(line >= MAXLINE) break;
            tft.println("   |                         |      |    |           ");
          }
          showTrailer(tft);
          
          Serial.println(j);
          if(j == n-12) endScroll = 1;
          if(Serial.available()) selected = 1;
        }

        if(digitalRead(UPBTN) == LOW)
        {
          if(j == 0) continue;
          j--;
          clearScreen(tft);
          showHeader(tft, n);
          tft.setTextColor(ILI9341_WHITE);
          line = 0;
          for(int i = j; i < n; i++)
          {
            line++;
            screenShowOnce(tft, i);
            if(line >= MAXLINE) break;
            tft.println("   |                         |      |    |           ");
          }
          showTrailer(tft);
          Serial.println(j);
          if(Serial.available()) selected = 1;
        }
      }
      if(digitalRead(UPBTN) == LOW) goto scroll;
}

void screenShow(Adafruit_ILI9341 &tft, int n)
{
  Serial.print(n);
  Serial.println(" networks found");
  Serial.println("No | SSID              | RSSI| CH | Encryption");
  
  showHeader(tft, n);

  tft.setTextColor(ILI9341_WHITE);
  for(int i = 0; i < n; i++)
  {
    screenShowOnce(tft, i);
  }
  showTrailer(tft);
}

void screenShowOnce(Adafruit_ILI9341 &tft, int i)
{
  
  // Print SSID and RSSI for each network found
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);

  Serial.printf("%2d",i + 1);
  Serial.print(" | ");
  Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
  Serial.print(" | ");
  Serial.printf("%4d", WiFi.RSSI(i));
  Serial.print(" | ");
  Serial.printf("%2d", WiFi.channel(i));
  Serial.print(" | ");

  tft.printf("%2d",i + 1);
  tft.print(" | ");
  tft.printf("%-23.23s", WiFi.SSID(i).c_str());
  tft.print(" | ");
  tft.printf("%4d", WiFi.RSSI(i));
  tft.print(" | ");
  tft.printf("%2d", WiFi.channel(i));
  tft.print(" | ");
  switch (WiFi.encryptionType(i))
  {
  case WIFI_AUTH_OPEN:
      Serial.print("open");
      tft.print("open");
      break;
  case WIFI_AUTH_WEP:
      Serial.print("WEP");
      tft.print("WEP");
      break;
  case WIFI_AUTH_WPA_PSK:
      Serial.print("WPA");
      tft.print("WPA");
      break;
  case WIFI_AUTH_WPA2_PSK:
      Serial.print("WPA2");
      tft.print("WPA2");
      break;
  case WIFI_AUTH_WPA_WPA2_PSK:
      Serial.print("WPA+WPA2");
      tft.print("WPA+WPA2");
      break;
  case WIFI_AUTH_WPA2_ENTERPRISE:
      Serial.print("WPA2-EAP");
      tft.print("WPA2-EAP");
      break;
  case WIFI_AUTH_WPA3_PSK:
      Serial.print("WPA3");
      tft.print("WPA3");
      break;
  case WIFI_AUTH_WPA2_WPA3_PSK:
      Serial.print("WPA2+WPA3");
      tft.print("WPA2+WPA3");
      break;
  case WIFI_AUTH_WAPI_PSK:
      Serial.print("WAPI");
      tft.print("WAPI");
      break;
  default:
      Serial.print("unknown");
      tft.print("unknown");
  }
  
      
  
  delay(10);
  Serial.println("");
  tft.println("");
  
}

void showHeader(Adafruit_ILI9341 &tft, int n)
{
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1);
  tft.print(n);
  tft.println(" networks found");
  tft.println("");
  tft.setTextColor(ILI9341_BLUE);
  tft.println("No | SSID                    | RSSI | CH | Encryption");
  tft.setTextColor(ILI9341_WHITE);
  tft.println("   |                         |      |    |           ");
}

void showTrailer(Adafruit_ILI9341 &tft)
{
  tft.setTextColor(ILI9341_GREEN);
  tft.println("");
  tft.println("Enter the no. of the network you want to connect");
}