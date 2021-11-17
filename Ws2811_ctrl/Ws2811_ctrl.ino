#include "Names.h"
//#define OTA_ENABLED

void setup() {
  Serial.begin(115200);
  scr_setup();
  if (wifi_setup() == 1) {
    web_setup();
    
#ifdef OTA_ENABLED
    ota_start();
#endif

  }

  led_setup();
  load_settings();

}

void loop() {

  led_loop();

#ifdef OTA_ENABLED
  ota_loop();
#endif


}
