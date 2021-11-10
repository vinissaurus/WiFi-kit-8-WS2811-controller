#include "Names.h"


void setup() {
  Serial.begin(115200);
  //wifi_setup();
//  if (WiFi.status == WL_CONNECTED) {
//    web_setup();
//  }
  //scr_setup();
  led_setup();
}

void loop() {
  //wifi_loop();
  led_loop();
  //scr_loop();
}
