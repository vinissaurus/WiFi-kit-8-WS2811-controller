#include "Names.h"

int clk = 0;

void setup() {
  Serial.begin(115200);
  //wifi_setup();
  //scr_setup();
  led_setup();
}

void loop() {
  clk = millis();
  //wifi_loop();
  led_loop();
  //scr_loop();
}
