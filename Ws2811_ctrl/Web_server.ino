#include "Pages.h"

char ipAdr[16];

void set_value(AsyncWebServerRequest *request) {
  if (request->hasParam("bright")) {
    set_led_brightness(request->getParam("bright")->value().toInt());
  }
  if (request->hasParam("speed")) {
    set_led_speed(request->getParam("speed")->value().toInt());
  }
  if (request->hasParam("cycle")) {
    set_led_cycle(request->getParam("cycle")->value().toInt());
  }
  if (request->hasParam("fadein")) {
    if (request->getParam("fadein")->value() == "on") {
      set_fadein(true);
    }
    if (request->getParam("fadein")->value() == "off") {
      set_fadein(false);
    }
  }
  if (request->hasParam("fadeout")) {
    if (request->getParam("fadeout")->value() == "on") {
      set_fadeout(true);
    }
    if (request->getParam("fadeout")->value() == "off") {
      set_fadeout(false);
    }
  }

  request->send(200, "text/plain", "{situacao: 0}" );
}

void change_anim(AsyncWebServerRequest *request) {
  String sign = request->getParam("d")->value();
  if (sign.equals("next")) {
    next_anim();
  }
  if (sign.equals("prev")) {
    prev_anim();
  }
  String response = "anim=" + animation_names[animation_mode];
  request->send(200, "text/plain", response  );
}

void refresh_fields() {
  ext_bright = get_led_brightness();
  ext_speed = get_led_speed();
  ext_cycle = get_led_cycle();
  time_on = get_on_time();
  time_off = get_off_time();
  switch (get_led_fade()) {
    case 0:
      time_fadein = 0;
      time_fadeout = 0;
      break;
    case 1:
      time_fadein = 1;
      time_fadeout = 0;
      break;
    case 2:
      time_fadein = 0;
      time_fadeout = 1;
      break;
    case 3:
      time_fadein = 1;
      time_fadeout = 1;
      break;
  }
  if (!anim_cycle) {
    actual_anim = animation_names[animation_mode];
  } else {
    actual_anim = "CYCLE ALL";
  }
}

void handleRoot(AsyncWebServerRequest *request) {
  refresh_fields();
  delay(500);
  request->send_P(200, "text/html", index_html , processor);
}

void handleNotFound(AsyncWebServerRequest *request) {
  String message = "{situacao: -1}";
  request->send(404, "text/plain", message);
}

void set_time(AsyncWebServerRequest *request) {
  int h1, m1, h2, m2;
  String on_input = request->getParam("on")->value();
  String off_input = request->getParam("off")->value();
  //Serial.println(on_input);
  //Serial.println(off_input);
  h1 = on_input.substring(0, on_input.indexOf(":")).toInt();
  m1 = on_input.substring(on_input.indexOf(":") + 1, on_input.length()).toInt();

  h2 = off_input.substring(0, off_input.indexOf(":")).toInt();
  m2 = off_input.substring(off_input.indexOf(":") + 1, off_input.length()).toInt();
  save_time(h1, m1, h2, m2);
  request->send(200, "text/plain", "{situacao: 0}" );
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
  webServer.on("/anim", change_anim);
  webServer.on("/time", set_time);
  webServer.onNotFound(handleNotFound);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers",  "Content-Type, Content-Range, Content-Disposition, Content-Description, Control-Allow-Headers, Cache-Control, Pragma, Expires, Access-Control-Allow-Headers, X-Requested-With");

#ifdef DISPLAY_ON
  sprintf(ipAdr, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  scr_out("Talk to me at:", ipAdr);
#endif
  webServer.begin();
}
