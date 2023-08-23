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
  // wifi_scan();
  // wifi_init();
      // Set WiFi to station mode and disconnect from an AP if it was previously connected.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done");
    scan();
    user();
    connect();
    // handlers();
}

void loop() 
{
  // scan();
  // wifi_init();
}

void scan()
{
    Serial.println("Scan start");
 
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    Serial.println("");

    // Delete the scan result to free memory for code below.
    // WiFi.scanDelete();
}
}

void user(){
Serial.println("Enter the no. of the network you want to connect:");
while (!Serial.available()) {
  // Wait for user input
}
int no_ssid = Serial.parseInt();
int selectedNetworkIndex = no_ssid - 1;

ssid = WiFi.SSID(selectedNetworkIndex);

Serial.print("Selected network: ");
Serial.println(ssid);

if (WiFi.encryptionType(selectedNetworkIndex) != WIFI_AUTH_OPEN)
 {
   // Read the password from serial input until a newline character is received
   while (Serial.read() != '\n') {
     // Wait for the newline character
   }
   Serial.println("Please enter the password of the network you choose:");
  
   while (true) {
     while (!Serial.available()) {
      // Wait for user input
      }

    pass = Serial.readString();
    pass.trim(); // Remove leading and trailing whitespace
    
    if (pass.length() >= 8) {
      Serial.print("Entered password: ");
      Serial.println(pass);
      break; // Exit the loop if the password length is sufficient
    } else {
      Serial.println("Password should be at least 8 characters. Please try again:");
    }
  }
}



}

void connect(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.println("\nConnecting to WiFi Network ..");
    Serial.println(ssid);
    Serial.println(pass);
    int WiFiStatus;
    int TimeOutCounter = 0;

    WiFiStatus = WiFi.status();

     while(WiFi.status() != WL_CONNECTED){
        Serial.println(Get_WiFiStatus(WiFiStatus));
        delay(100);
        TimeOutCounter++;
        if(TimeOutCounter >= 100)
        {
          Serial.println("Resetting due to Wifi not connecting...");
          ESP.restart();
        }
    }
    // Connected Successfully
    Serial.println("\nConnected To The WiFi Network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    // handlers();
}
void handlers(){


}


String Get_WiFiStatus(int Status){
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