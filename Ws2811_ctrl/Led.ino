#include <FastLED.h>
#include "Animation.h"
FASTLED_USING_NAMESPACE

#define LED_PIN 15 //"D8"
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BUTTON 12 //"D6"
#define BUTTON_RATE 10

int CYCLE_TROUGH = 50;//20-100

bool anim_play = true;
int animation_mode = 5;
int max_anim = 6;

void led_setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(BUTTON, INPUT);
}



void set_led_brightness(int new_brightness) {
  BRIGHTNESS = new_brightness;
  FastLED.setBrightness( BRIGHTNESS );
  //Serial.println("Changed brightness to:");
  //Serial.println(BRIGHTNESS);
}

int get_led_brightness() {
  return BRIGHTNESS;
}

int get_led_speed() {
  return 100-RATE;
}

void set_led_speed(int new_speed) {
  RATE = 100 - new_speed;
}

int get_led_cycle() {
  return CYCLE_TROUGH;
}

void set_led_cycle(int new_cycle) {
  CYCLE_TROUGH = new_cycle;
}

void next_anim() {
  if (animation_mode < max_anim) {
    animation_mode++;
    display_animation_mode();
  }
  else {
    animation_mode = 0;
  }
  display_animation_mode();
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
      case 0://OFF
        fadeall();
        break;
      //      case 1://CYCLE THROUG MODES
      //
      //        break;
      case 2:
        Fire();
        break;
      case 3:
        Ocean();
        break;
      case 4:
        Palette();
        break;
      case 5:
        pride();
        break;
      case 6:
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
