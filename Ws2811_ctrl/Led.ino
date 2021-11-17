#include <FastLED.h>
#include "Animation.h"
FASTLED_USING_NAMESPACE

#define LED_PIN 15 //"D8"
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BUTTON 12 //"D6"
#define BUTTON_RATE 10

int CYCLE_TROUGH = 250;//20-100

bool anim_play = true;

int max_anim = 5;
bool anim_cycle=false;

void led_setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(BUTTON, INPUT);
  if(animation_mode==1){
    anim_cycle=true;
    }
    
}


void set_led_brightness(int new_brightness) {
  BRIGHTNESS = new_brightness;
  FastLED.setBrightness( BRIGHTNESS );
  save_brightness(BRIGHTNESS);
  //Serial.println("Changed brightness to:");
  //Serial.println(BRIGHTNESS);
}

int get_led_brightness() {
  return BRIGHTNESS;
}

int get_led_speed() {
  return 100 - RATE;
}

void set_led_speed(int new_speed) {
  RATE = 100 - new_speed;
  save_speed(RATE);
}

int get_led_cycle() {
  return CYCLE_TROUGH;
}

void set_led_cycle(int new_cycle) {
  CYCLE_TROUGH = new_cycle;
  save_cycle_time(CYCLE_TROUGH);

}

void next_anim() {
  if (animation_mode < max_anim) {
    animation_mode++;
    display_animation_mode();
    if (animation_mode == 1) {
    anim_cycle=true;
    animation_mode++;
    }else{anim_cycle=false;}
  }
  else {
    animation_mode = 0;
  }
  
  display_animation_mode();
  save_animation();
}

void prev_anim() {
  if (animation_mode > 0) {
    animation_mode--;
    display_animation_mode();
  }
  else {
    animation_mode = max_anim;
  }
  
  display_animation_mode();
  save_animation();
}
//ANIMATIONS HERE

///////////////////////////NOT ANYMORE, BEEATCH! PLEASE VISIT "Animation.h" for more info

//ANIMATIONS HEHE


int button_counter = 0;
//int repeated_press = 0;

void display_animation_mode() {
  scr_out("Animation mode:", animation_names[animation_mode]);
}

void button_press(int time_pressed) {
  //if (time_pressed > 10) {
  Serial.println(time_pressed);
  //}
  if (time_pressed > 5 && time_pressed < 30) {
    //anim_play = !anim_play; //play or pause
    next_anim();
  }
}

void button_loop() {
  switch (digitalRead(BUTTON)) {
    case LOW:
      if (button_counter > 0) {
        button_press(button_counter);
        button_counter = 0;
        //repeated_press++;
      }
      break;
    case HIGH:
      //Serial.println("Piá");
      button_counter++;
      break;
  }
}

int led_ck = 0;
int button_ck = 0;
int cycle_counter=0;

void led_loop() {
  if (millis() >= led_ck + RATE) {
    led_ck = millis();    
    
    switch (animation_mode) {
      case 0://OFF
        fadeall();
        break;
      //      case 1://CYCLE THROUG MODES
      //
      //        break;
//      case 2:
//        Fire();
//        break;
      case 2:
        Ocean();
        break;
      case 3:
        Palette();
        break;
      case 4:
        pride();
        break;
      case 5:
        TwinkleFox();
        break;
    }

    FastLED.show();
  }

      if(anim_cycle && millis() >=cycle_counter+CYCLE_TROUGH*1000){
        cycle_counter=millis();
        if(animation_mode<max_anim){
          animation_mode++;
          if(animation_mode==1){
            animation_mode++;
            }
          }else{
            animation_mode=0;
            }
        }
  
  if (millis() >= button_ck + BUTTON_RATE) {
    button_ck = millis();
    button_loop();
  }
}
