#include "Names.h"
//#include "Display.h"
//#define OTA_ENABLED
#define DNS_ON


void setup() {
  Serial.begin(115200);
  load_settings();
  wifi_setup();


#ifdef OTA_ENABLED
  ota_start();
#endif


#ifdef DISPLAY_ON
  scr_setup();
#endif

  web_setup();
  led_setup();
}

void loop() {
  led_loop();
#ifdef OTA_ENABLED
  ota_loop();
#endif
#ifdef DNS_ON
  dns_loop();
#endif
}
