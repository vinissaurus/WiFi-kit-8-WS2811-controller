#include "Names.h"
//#include "Display.h"
//#define OTA_ENABLED
#define DNS_ON


void setup() {
  Serial.begin(115200);
  wifi_setup();
  load_settings();
  web_setup();
  led_setup();

#ifdef OTA_ENABLED
  ota_start();
#endif
#ifdef DISPLAY_ON
  scr_setup();
#endif
}

void loop() {
  led_loop();
  timed_schedule_loop();
#ifdef OTA_ENABLED
  ota_loop();
#endif
#ifdef DNS_ON
  dns_loop();
#endif
}
