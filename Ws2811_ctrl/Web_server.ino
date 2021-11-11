//#include <ESPAsyncTCP.h>
//#include <ESPAsyncWebServer.h>
//#include <ESP8266WiFi.h>
#include "Pages.h"
#define WEB_RATE 50
ESP8266WebServer server(80);
char ipAdr[16];

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

void handleRoot() {
  server.send(200, "text/plain", "Hello Pir");
}

void web_setup() {

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    //return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  // DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  //DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers",  "Content-Type, Content-Range, Content-Disposition, Content-Description, Control-Allow-Headers, Cache-Control, Pragma, Expires, Access-Control-Allow-Headers, X-Requested-With");

  sprintf(ipAdr, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  scr_out("Talk to me at:", ipAdr);
  server.begin();
}

int web_ck = 0;
void web_loop() {
  if (millis() >= web_ck + WEB_RATE) {
    web_ck = millis();
    server.handleClient();
  }
}
