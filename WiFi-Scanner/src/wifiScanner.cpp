#include "wifiScanner.h"
#include "tftScreen.h"

int n = 0;
String ssid = "";
String pass = "";

int wifiScan(Adafruit_ILI9341 &tft)
{
  tft.begin();
  tft.setRotation(1);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Connecting to WiFi");
  n = WiFi.scanNetworks();
  //n=20;
  int x = WiFi.scanComplete();
  Serial.println("Scan started");
  clearScreen(tft);
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

  return x;
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
        tft.print(".");
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
        
        while (true) {
        while (!Serial.available()) {
          // Wait for user input
          }

        pass = Serial.readString();
        pass.trim(); // Remove leading and trailing whitespace
        
        if (pass.length() >= 8) {
          for(int i = 0; i < pass.length(); i++) tft.print("*");
          tft.println();
          break; // Exit the loop if the password length is sufficient
        } else {
          Serial.println("Password should be at least 8 characters. Please try again:");
          tft.println("Password should be at least 8 characters. Please try again:");
        }
      }
        
        
    }
    else
    {
        pass = "";
    }
}

/*
String getWiFiStatus(int Status){
    switch(Status){
        case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
        case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
        case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
        case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
        case WL_CONNECTED:
        return "WL_CONNECTED";
        case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    }
}
*/