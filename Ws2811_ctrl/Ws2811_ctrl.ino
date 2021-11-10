#include "Names.h"


void setup() {
  Serial.begin(115200);

  if (wifi_setup() == 1) {
    web_setup();
  }
  //scr_setup();
  led_setup();

}

void loop() {
  wifi_loop();
  led_loop();
  web_loop();
  //scr_loop();
}
