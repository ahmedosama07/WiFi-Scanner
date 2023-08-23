#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

String ssid = "";
String pass = "";

unsigned long timestart = 0;
unsigned long timeout=0;

int n = 0;
int trial = 0;

#define downBtn 5

#define TFT_DC 2
#define TFT_CS 15
#define MAXLINE 11
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void wifi_scan()
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

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);

  if(n == 0)
  {
    Serial.println("Not networks found");
    tft.println("Not networks found");
  }
  else
  {
    int j = 1;
    //Serial.print("hhhhhhhhhhh: ");
    //Serial.println(n);
    if(n > MAXLINE)
    {
      int line = 0;
      tft.fillScreen(ILI9341_BLACK);
      tft.setCursor(0, 0);
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
          tft.fillScreen(ILI9341_BLACK);
          tft.setCursor(0, 0);
          tft.setTextColor(ILI9341_GREEN);
          tft.print(n);
          tft.println(" networks found");
          tft.setTextColor(ILI9341_BLUE);
          //tft.setCursor(0, 2);
          //tft.println("");
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
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
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

void wifi_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);

  Serial.print("Connecting to Wifi...");
  tft.print("Connecting to Wifi...");
  timeout = millis();
  while((WiFi.status() != WL_CONNECTED) && (millis() - timeout < 8000))
  {
    Serial.print(".");
    delay(1000);
  }

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  

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
  pinMode(downBtn, INPUT_PULLUP);

  Serial.begin(115200);
  

  wifi_scan();
  wifi_init();

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