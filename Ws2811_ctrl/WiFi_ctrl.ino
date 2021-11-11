#include <ESPAsync_WiFiManager.h>//https://github.com/khoih-prog/ESPAsync_WiFiManager
DNSServer dnsServer;

ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "AutoConnectAP");

int wifi_setup() {
  scr_out("Connecting...","wait prease");
  int is_it_connected=0;

  Serial.print("\nStarting Async_AutoConnect_ESP8266_minimal on " + String(ARDUINO_BOARD)); Serial.println(ESP_ASYNC_WIFIMANAGER_VERSION);
  
  //ESPAsync_wifiManager.resetSettings();   //reset saved settings
  //ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192,168,186,1), IPAddress(192,168,186,1), IPAddress(255,255,255,0));
  ESPAsync_wifiManager.autoConnect("AutoConnectAP");
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP()); 
    is_it_connected=1;
    }
  else { 
    Serial.println(ESPAsync_wifiManager.getStatus(WiFi.status())); 
    }
  
  return is_it_connected;
}



void wifi_reset() {
  ESPAsync_wifiManager.resetSettings();
  Serial.println("Just erased wifi config");
  scr_out("Credentials","deleted!");
}
