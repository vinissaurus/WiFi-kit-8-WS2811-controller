#include <FastLED.h>
#include "Animation.h"
FASTLED_USING_NAMESPACE

#define LED_PIN 15 //"D8"
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BUTTON 12 //"D6"
#define BUTTON_RATE 10

void led_setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(BUTTON, INPUT);
}

void set_led_speed(int new_speed) {
  RATE = new_speed;
}

void set_led_brightness(int new_brightness) {
  BRIGHTNESS = new_brightness;
}
//ANIMATIONS HERE

///////////////////////////NOT ANYMORE, BEEATCH! PLEASE VISIT "Animation.h" for more info

//ANIMATIONS HEHE
bool anim_play = true;
int animation_mode = 5;

int button_counter = 0;
//int repeated_press = 0;

void display_animation_mode(){
      switch (animation_mode) {
      case 0:
        //Cylon();
        animation_mode++;
        break;
      case 1:
        //Fire();
        scr_out("Fyre","festival");
        break;
      case 2:
        //Ocean();
        scr_out("Wave","rly");
        break;
      case 3:
        //Palette();
        scr_out("Colours","by benetton");
        break;
      case 4:
        //pride();
        scr_out("Pride","people");
        break;
      case 5:
        //TwinkleFox();
        scr_out("Happy","holydays");
        break;
    }
  }

void button_press(int time_pressed) {
  //if (time_pressed > 10) {
  Serial.println(time_pressed);
  //}
  if (time_pressed > 5 && time_pressed < 30) {
    //anim_play = !anim_play; //play or pause
    if (animation_mode < 5) {
      animation_mode++;
      display_animation_mode();
    }
    else {
      animation_mode = 0;
    }
    //Serial.println(anim_play);
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

void led_loop() {
  if (millis() >= led_ck + RATE && anim_play) {
    led_ck = millis();

    switch (animation_mode) {
      case 0:
        //Cylon();
        animation_mode++;
        break;
      case 1:
        Fire();
        break;
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
  if (millis() >= button_ck + BUTTON_RATE) {
    button_ck = millis();
    button_loop();
  }
}
