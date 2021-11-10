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
//ANIMATIONS HERE

///////////////////////////NOT ANYMORE, BEEATCH! PLEASE VISIT "Animation.h" for more info

//ANIMATIONS HEHE
bool anim_play = true;
int animation_mode = 4;

int button_counter = 0;

void button_press(int time_pressed) {
  //if (time_pressed > 10) {
  Serial.println(time_pressed);
  //}
  if (time_pressed > 5 && time_pressed < 30) {
    anim_play = !anim_play; //play or pause
    Serial.println(anim_play);
  }
}

void button_loop() {
  switch (digitalRead(BUTTON)) {
    case LOW:
      if (button_counter > 0) {
        button_press(button_counter);
        button_counter = 0;
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
        Cylon();
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
    }

    FastLED.show();
  }
  if (millis() >= button_ck + BUTTON_RATE) {
    button_ck = millis();
    button_loop();
  }
}
