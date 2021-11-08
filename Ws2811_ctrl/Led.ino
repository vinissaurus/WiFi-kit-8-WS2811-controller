#include <FastLED.h>
#include "Animation.h"
FASTLED_USING_NAMESPACE

#define LED_PIN 15 //D3
#define COLOR_ORDER RGB
#define CHIPSET WS2811

void led_setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}
//ANIMATIONS HERE

///////////////////////////NOT ANYMORE, BEEATCH! PLEASE VISIT "Animation.h" for more info

//ANIMATIONS HEHE
int animation_mode = 2;

int led_counter = 0;
void led_loop() {
  if (millis() >= led_counter + RATE) {
    led_counter = millis();

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
    }

    FastLED.show();
  }
}
