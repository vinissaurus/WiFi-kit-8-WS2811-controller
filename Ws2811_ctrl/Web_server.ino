#include "Pages.h"

char ipAdr[16];

void set_value(AsyncWebServerRequest *request) {
  if (request->hasParam("bright")) {
    set_led_brightness(request->getParam("bright")->value().toInt());
  }
    if (request->hasParam("speed")) {
    set_led_speed(request->getParam("speed")->value().toInt());
  }

  request->send(200, "text/plain", "{situacao: 0}" );
}

void refresh_fields(){
  ext_bright=get_led_brightness();
  ext_speed=get_led_speed();
  }

void handleRoot(AsyncWebServerRequest *request) {
  refresh_fields();
  request->send_P(200, "text/html", index_html , processor);
}

void handleNotFound(AsyncWebServerRequest *request) {
  String message = "{situacao: -1}";
  request->send(404, "text/plain", message);
}


void web_setup() {

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    //return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  webServer.on("/", handleRoot);
  webServer.on("/set", set_value);
  webServer.onNotFound(handleNotFound);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers",  "Content-Type, Content-Range, Content-Disposition, Content-Description, Control-Allow-Headers, Cache-Control, Pragma, Expires, Access-Control-Allow-Headers, X-Requested-With");

  sprintf(ipAdr, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  scr_out("Talk to me at:", ipAdr);
  webServer.begin();
}
