#include <ESPAsyncWebServer.h>
#define NUM_LEDS 50

AsyncWebServer webServer(80);

String animation_names[] = {"OFF","CYCLE ALL","Fire","Ocean","Palette","Pride!","Christmas"};

void led_setup();
void led_loop();

void set_led_speed(int new_speed);
void set_led_brightness(int new_brightness);
void set_led_cycle(int new_cycle);
int get_led_brightness();
int get_led_speed();
int get_led_cycle();
void next_anim();
void prev_anim();


//void scr_loop();
void scr_setup();
void scr_out(String a, String b);

void web_setup();
int wifi_setup();
#ifdef OTA_ENABLED
void ota_start();
void ota_loop();
#endif

void load_settings();
void read_time();
int get_on_time();
int get_off_time();
void save_time(int H_ON,int M_ON,int H_OFF,int M_OFF);
