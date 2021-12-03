#include <ESPAsync_WiFiManager.h>//https://github.com/khoih-prog/ESPAsync_WiFiManager

#ifdef DNS_ON
#include <ESP8266mDNS.h>
#define DNS_NAME "wesp2811"
#endif

#define ESP_DRD_USE_EEPROM false

#ifdef OTA_ENABLED
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#endif
//#define SCHEMA_ON

DNSServer dnsServer;

ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "AutoConnectAP");

int wifi_setup() {
#ifdef DISPLAY_ON
  scr_out("Connecting...", "wait prease");
#endif
  int is_it_connected = 0;
  Serial.println(ESP_ASYNC_WIFIMANAGER_VERSION);
  load_credentials();

  //Serial.println(memSSID);
  if (memPSK != "@null") {
    WiFi.mode(WIFI_STA);
    WiFi.begin(memSSID.c_str(), memPSK.c_str());
    if (WiFi.status() == WL_CONNECTED) {
      goto finished;
    }
  }
  ESPAsync_wifiManager.autoConnect("AutoConnectAP");
  ESPAsync_wifiManager.setConfigPortalTimeout(360);
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(ESPAsync_wifiManager.WiFi_SSID());
    memSSID = ESPAsync_wifiManager.WiFi_SSID();
    memPSK = ESPAsync_wifiManager.WiFi_Pass();
    save_credentials();
    //Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP());
    is_it_connected = 1;
  }

finished:
  WiFi.softAPdisconnect(true);
  Serial.println(ESPAsync_wifiManager.getStatus(WiFi.status()));
  Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP());

#ifdef SCHEMA_ON
  //  //SSDP.schema(webServer());
  //  SSDP.setSchemaURL("description.xml");
  //  SSDP.setHTTPPort(80);
  //  SSDP.setName("Philips hue clone");
  //  SSDP.setSerialNumber("001788102201");
  //  SSDP.setURL("index.html");
  //  SSDP.setModelName("Philips hue bridge 2012");
  //  SSDP.setModelNumber("929000226503");
  //  SSDP.setModelURL("http://www.meethue.com");
  //  SSDP.setManufacturer("Royal Philips Electronics");
  //  SSDP.setManufacturerURL("http://www.philips.com");
  //  SSDP.begin();
#endif

#ifdef DNS_ON
  if (is_it_connected == 1) {
    dns_begin();
  }
#endif

  return is_it_connected;
}



void wifi_reset() {
  ESPAsync_wifiManager.resetSettings();
  Serial.println("Just erased wifi config");
#ifdef DISPLAY_ON
  scr_out("Credentials", "deleted!");
#endif
}



#ifdef OTA_ENABLED
void ota_start() {
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  //ArduinoOTA.setPassword("bass");

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

#ifdef DNS_ON


void dns_begin() {
  if (!MDNS.begin(DNS_NAME)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
}

void dns_loop() {
  MDNS.update();
}
#endif
