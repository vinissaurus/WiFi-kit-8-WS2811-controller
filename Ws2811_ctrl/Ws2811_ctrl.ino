#include "Names.h"
//#define OTA_ENABLED
//#define DISPLAY

void setup() {
  Serial.begin(115200);
  scr_setup();
  if (wifi_setup() == 1) {
    web_setup();

#ifdef OTA_ENABLED
    ota_start();
#endif

  }
  load_settings();
  led_setup();


}

void loop() {

  led_loop();

#ifdef OTA_ENABLED
  ota_loop();
#endif


}
