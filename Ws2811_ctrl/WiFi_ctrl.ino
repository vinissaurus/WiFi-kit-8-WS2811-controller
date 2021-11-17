#include <ESPAsync_WiFiManager.h>//https://github.com/khoih-prog/ESPAsync_WiFiManager

#ifdef OTA_ENABLED
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#endif
DNSServer dnsServer;

ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "AutoConnectAP");

int wifi_setup() {
  scr_out("Connecting...", "wait prease");
  int is_it_connected = 0;

  Serial.print("\nStarting Async_AutoConnect_ESP8266_minimal on " + String(ARDUINO_BOARD)); Serial.println(ESP_ASYNC_WIFIMANAGER_VERSION);

  //ESPAsync_wifiManager.resetSettings();   //reset saved settings
  //ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192,168,186,1), IPAddress(192,168,186,1), IPAddress(255,255,255,0));
  ESPAsync_wifiManager.autoConnect("AutoConnectAP");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP());
    is_it_connected = 1;
  }
  else {
    Serial.println(ESPAsync_wifiManager.getStatus(WiFi.status()));
  }

  return is_it_connected;
}

#ifdef OTA_ENABLED
void ota_start() {
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  ArduinoOTA.setPassword("adumbass");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}

void ota_loop() {
  ArduinoOTA.handle();
}
#endif

void wifi_reset() {
  ESPAsync_wifiManager.resetSettings();
  Serial.println("Just erased wifi config");
  scr_out("Credentials", "deleted!");
}
