#include <ESPAsyncWebServer.h>
#define NUM_LEDS 50

AsyncWebServer webServer(80);
String memSSID, memPSK;

String animation_names[] = {"OFF","CYCLE ALL","Ocean","Palette","Pride!","Christmas"};
int animation_mode = 1;
bool anim_cycle=false;

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

void web_setup();
int wifi_setup();
#ifdef OTA_ENABLED
void ota_start();
void ota_loop();
#endif

void load_settings();
void read_time();
void save_animation();
void save_brightness(int new_brighness);
void save_speed(int new_speed);
void save_cycle_time(int new_cycle_time);
//void get_animation();
int get_on_time();
int get_off_time();
void save_time(int H_ON,int M_ON,int H_OFF,int M_OFF);
void save_credentials();
void load_credentials();
void delete_credentials();
