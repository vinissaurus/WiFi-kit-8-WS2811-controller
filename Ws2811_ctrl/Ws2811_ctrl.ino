#include "Names.h"


void setup() {
  Serial.begin(115200);
  scr_setup();
  if (wifi_setup() == 1) {
    web_setup();
  }
  
  led_setup();
  load_settings();

}

void loop() {
//  wifi_loop();
  led_loop();
  //web_loop();
  //scr_loop();
}
