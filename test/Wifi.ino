#include "WiFi.h"

String ssid = "";
String pass = "";

unsigned long timestart = 0;
unsigned long timeout=0;

int n = 0;
int trial = 0;

void setup()
{
  Serial.begin(115200);
  wifi_scan();
  wifi_init();
}

void loop()
{
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





void wifi_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to Wifi...");
  timeout = millis();
  while((WiFi.status() != WL_CONNECTED) && (millis() - timeout < 8000))
  {
    Serial.print(".");
    delay(1000);
  }
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Can't connect to wifi");
  }
  else
  {
    Serial.println("");
    Serial.println("Connected successfully");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
    trial = 0;
  }
  
}

void wifi_scan()
{
  
  n = WiFi.scanNetworks();
  int x = WiFi.scanComplete();
  Serial.println(x);

  Serial.println("Scan started");
  delay(500);

  if(n == 0)
  {
    Serial.println("Not networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");

    for(int i = 0; i < n; i++)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      if((WiFi.encryptionType(i) == WIFI_AUTH_OPEN))
      {
        Serial.println("*");
      }
      delay(10);
      Serial.println("");
    }
  }
  
  Serial.println("Enter the no. of the network you want to connect");
  while (Serial.available() == 0){}
  int no_ssid = Serial.parseInt();
  ssid = WiFi.SSID(no_ssid - 1);  
  
  if((WiFi.encryptionType(no_ssid - 1) != WIFI_AUTH_OPEN))
  {
    Serial.println("Please enter the password of the network you chose");
    while (Serial.available() == 0){}
    pass = Serial.readString();
  }
  else
  {
    pass = "";
  }

}
