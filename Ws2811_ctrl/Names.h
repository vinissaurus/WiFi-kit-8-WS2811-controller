#include <WiFiManager.h>
#define NUM_LEDS 50

int wifi_setup();
void wifi_loop();

void led_setup();
void led_loop();

void set_led_speed();
void set_led_brightness();

//void scr_loop();
void scr_setup();
void scr_out(String a, String b);

void web_setup();
void web_loop();
