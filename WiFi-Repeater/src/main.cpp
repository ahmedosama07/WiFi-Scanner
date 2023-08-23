#include <WiFi.h>

const char* wifi_network_ssid     = "OPPO Reno8";   /*Replace with Your own network SSID*/
const char* wifi_network_password =  "fmctkuea"; /*Replace with Your own network PASSWORD*/
const char *soft_ap_ssid          = "ESP32";    /*Create a SSID for ESP32 Access Point*/
const char *soft_ap_password      = "123456789"; /*Create Password for ESP32 AP*/
void setup()
{
    Serial.begin(115200);  /*Baud rate for serial communication*/
    WiFi.mode(WIFI_AP_STA);  /*ESP32 Access point configured*/
    Serial.println("\n[*] Creating ESP32 AP");
    IPAddress gateway(192, 168, 216, 106);
    IPAddress local_ip(192, 168, 216, 107);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(soft_ap_ssid, soft_ap_password);  /*Configuring ESP32 access point SSID and password*/
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());     /*Printing the AP IP address*/
    WiFi.begin(wifi_network_ssid, wifi_network_password);  /*Connecting to Defined Access point*/
    Serial.println("\n[*] Connecting to WiFi Network");
    
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
    Serial.print("\n[+] Connected to WiFi network with local IP : ");
    Serial.println(WiFi.localIP());   /*Printing IP address of Connected network*/
}
void loop() {}