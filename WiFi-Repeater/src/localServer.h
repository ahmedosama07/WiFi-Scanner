#ifndef WM_H
#define WM_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include <LITTLEFS.h>


#if (ARDDUINO >=100)
  #include "Arduino.h"
#endif


class WM {
  public:
  
  void listDir(const char * dirname);
  void begin_server();
  void create_server();
  String get_credentials(int a);
  
};

#endif