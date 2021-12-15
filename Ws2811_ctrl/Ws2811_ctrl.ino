#include "Names.h"
//#include "Display.h"
//#define OTA_ENABLED
#define DNS_ON
int wifi_status = 0;
//I hope I can comment every function in this code before I die, because there are too many, and it's a little complex

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(F("\nWS2811_Control \nby VSSAURUS - 2021 \ngithub.com/vinissaurus"));

  if (wifi_setup() == 1) {
    wifi_status = 1;
    web_setup();
  }
  load_settings();
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

#ifdef DNS_ON
  if (wifi_status == 1) {
    dns_loop();
  }
#endif

#ifdef OTA_ENABLED
  ota_loop();
#endif
}
