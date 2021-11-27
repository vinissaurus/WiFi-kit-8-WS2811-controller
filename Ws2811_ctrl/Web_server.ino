#include "Pages.h"

char message_200[]="{Ok!U+1F44D}";
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
  if (request->hasParam("timezone")) {
    //Serial.println(String(request->getParam("timezone")->value()));
    set_timezone(request->getParam("timezone")->value().toInt());
  }
  if (request->hasParam("on_sched")) {
    if (request->getParam("on_sched")->value() == "on") {
      save_time_schedule(true);
    }
    if (request->getParam("on_sched")->value() == "off") {
      save_time_schedule(false);
    }
  }

  request->send(200, "text/plain", message_200 );
}

void change_anim(AsyncWebServerRequest *request) {
  String sign = request->getParam("d")->value();
  if (sign.equals("next")) {
    next_anim();
  }
  if (sign.equals("prev")) {
    prev_anim();
  }

  String response = "anim=";
  if (!anim_cycle) {
    response += animation_names[animation_mode];
  } else {
    response += actual_anim = "CYCLE ALL";
  }
  request->send(200, "text/plain", response  );
}

String _fields() {
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
  
  time_on = get_on_time();
  time_off = get_off_time();
  int h1, m1, h2, m2;
  h1 = (time_on - time_on % 100) / 100;
  m1 = time_on % 100;
  h2 = (time_off - time_off % 100) / 100;
  m2 = time_off % 100;  
  char buffer[20];
  sprintf(buffer, "%02d:%02d;%02d:%02d", h1, m1 , h2, m2);

  //var received_text = "50;32;53;debug;true;true;true;12:23;00:01;-11";
  String response = "s=" +
                    String(get_led_brightness()) + ";" +
                    String(get_led_speed()) + ";" +
                    String(get_led_cycle()) + ";" +
                    actual_anim + ";" +
                    (time_fadein == 1 ? "t" : "f") + ";" +
                    (time_fadeout == 1 ? "t" : "f") + ";" +
                    (get_time_schedule() == 1 ? "t" : "f") + ";" +
                    buffer + ";" +
                    String(get_timezone());
  return response;
}

void handleRoot(AsyncWebServerRequest *request) {
  //refresh_fields();
  //request->send_P(200, "text/html", index_html, processor);
  request->send_P(200, "text/html", index_html);
  //  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
  //  response->addHeader("Server", "ESP Async Web Server");
  //  request->send(response);
}

void send_status(AsyncWebServerRequest *request) {

  request->send(200, "text/plain", _fields());
}

//void send_css(AsyncWebServerRequest *request) {
//  request->send(200, "text/css", style_css);
//}

void handleNotFound(AsyncWebServerRequest *request) {
 
  request->send(404, "text/plain", message_200);
}

void delete_ssid(AsyncWebServerRequest *request) {
  delete_credentials();
  
  request->send(200, "text/plain", message_200 );
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
  request->send(200, "text/plain", message_200 );
}

//void ssdp(AsyncWebServerRequest *request){
//  SSDP.schema(request);
//  request->send(200, "text/plain", message_200 );
//  }

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
  //webServer.on("/description.xml", ssdp) {
  webServer.on("/reset", delete_ssid);
  webServer.on("/status", send_status);
  //webServer.on("/style.css", send_css);
  webServer.onNotFound(handleNotFound);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers",  "Content-Type, Content-Range, Content-Disposition, Content-Description, Control-Allow-Headers, Cache-Control, Pragma, Expires, Access-Control-Allow-Headers, X-Requested-With");

#ifdef DISPLAY_ON
  sprintf(ipAdr, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  scr_out("Talk to me at:", ipAdr);
#endif
  webServer.begin();
}
