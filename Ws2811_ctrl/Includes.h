// ONLY EXTERNAL LIBRARIES SHOULD BE INCLUDED HERE
#include <FastLED.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncDNSServer.h>
#include <EEPROM.h>
#include <NTPClient.h>//https://github.com/arduino-libraries/NTPClient
#include <WiFiUdp.h>
#include <ESPAsync_WiFiManager.h>

#ifdef OTA_ENABLED
#include <ArduinoOTA.h>
#endif