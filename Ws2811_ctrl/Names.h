#include <ESPAsyncWebServer.h>
//#include <ESP8266SSDP.h>
#define NUM_LEDS 100

AsyncWebServer webServer(80);
String memSSID, memPSK;

//------------------------------------------------------LED
int max_anim = 14;
String animation_names[] = {"OFF",
                            "CYCLE ALL",
                            "Ocean",
                            "Christmas" ,
                            "Pride!",
                            "Palette[Rainbow]",
                            "Palette[Purple&Green]",
                            "Palette[Random]",
                            "Palette[B&W I]",
                            "Palette[B&W II]",
                            "Palette[B&W III]",
                            "Palette[Cloud]" ,
                            "Palette[Party]", 
                            "Palette[R&W&B I]",
                            "Palette[R&W&B II]"
                           };
int animation_mode = 1;

void led_setup();
void led_loop();
void animation_state(bool anim_on);
void set_fadein(bool in);
void set_fadeout(bool out);
void set_led_fade(int new_fade);
int get_led_fade();
void set_led_speed(int new_speed);
void set_led_brightness(int new_brightness);
void set_led_cycle(int new_cycle);
String get_animation_name();
int get_led_brightness();
int get_led_speed();
int get_led_cycle();
void next_anim();
void prev_anim();
//------------------------------------------------------LED

//------------------------------------------------------WiFi_ctrl
void web_setup();
int wifi_setup();
void ota_start();
void ota_loop();
void dns_begin();
void dns_loop();
//------------------------------------------------------WiFi_ctrl

//------------------------------------------------------Settings
void load_settings();
void timed_schedule_loop();
void save_time_schedule(bool ts);
int get_animation_mode();
bool get_time_schedule();
void read_time();
void save_animation();
void save_brightness(int new_brighness);
void save_speed(int new_speed);
void save_cycle_time(int new_cycle_time);
void save_fade_settings(int new_settings);
//void get_animation();
int get_on_time();
int get_off_time();
void save_time(int H_ON, int M_ON, int H_OFF, int M_OFF);
void save_credentials();
int get_timezone();
void set_timezone(int new_timezone);
void load_credentials();
void delete_credentials();
//------------------------------------------------------Settings
