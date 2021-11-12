#include <ESPAsyncWebServer.h>
#define NUM_LEDS 50

AsyncWebServer webServer(80);

void led_setup();
void led_loop();

void set_led_speed(int new_speed);
void set_led_brightness(int new_brightness);
int get_led_brightness();
int get_led_speed();

//void scr_loop();
void scr_setup();
void scr_out(String a, String b);

void web_setup();
int wifi_setup();
