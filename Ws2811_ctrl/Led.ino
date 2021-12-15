#include <FastLED.h>
#include "Animation.h"
FASTLED_USING_NAMESPACE

//#define LED_PIN 15 //"D8"
#define LED_PIN 13
#define COLOR_ORDER RGB
#define CHIPSET WS2811
//#define BUTTON 12 //"D6"
#define BUTTON 10
#define BUTTON_RATE 10

uint8_t CYCLE_THROUGH = 250;//20-100

bool anim_play = true;

int step_counter = 0;
int cycle_steps = 0;

bool fade_in = false;
bool fade_out = false;
bool state_changed = false;
uint8_t anim_sequence[max_anim - 2];
void generate_sequence();

void display_animation_mode() {
#ifdef DISPLAY_ON
  scr_out("Animation mode:", animation_names[animation_mode]);
#endif
}

void led_setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  //max_anim = sizeof(animation_names);
  pinMode(BUTTON, INPUT);
  randomSeed(analogRead(A0));
  generate_sequence();
}

void animation_state(bool anim_on) {
  if (anim_on) {
    animation_mode = get_animation_mode();
    if (animation_mode == 0) {
      animation_mode = 1;
    }
  } else {
    animation_mode = 0;
  }
}

void set_fadein(bool in) {
  fade_in = in;
  set_led_fade(get_led_fade());
}

void set_fadeout(bool out) {
  fade_out = out;
  set_led_fade(get_led_fade());
}

void set_led_fade(int new_fade) {
  switch (new_fade) {
    case 0:
      fade_in = false;
      fade_out = false;
      break;
    case 1:
      fade_in = true;
      fade_out = false;
      break;
    case 2:
      fade_in = false;
      fade_out = true;
      break;
    case 3:
      fade_in = true;
      fade_out = true;
      break;
  }
  save_fade_settings(new_fade);
}

int get_led_fade() {
  if (!fade_in && !fade_out)
    return 0;
  if (fade_in && !fade_out)
    return 1;
  if (!fade_in && fade_out)
    return 2;
  if (fade_in && fade_out)
    return 3;
}

void set_led_brightness(int new_brightness) {
  BRIGHTNESS = new_brightness;
  FastLED.setBrightness( BRIGHTNESS );
  save_brightness(BRIGHTNESS);
  cycle_steps = 25 * CYCLE_THROUGH - BRIGHTNESS;
  //Serial.println("Changed brightness to:");
  //Serial.println(BRIGHTNESS);
}

void set_led_brightness_d(int new_brightness) {//Directly change brightness without saving to EEPROM
  BRIGHTNESS = new_brightness;
  FastLED.setBrightness( BRIGHTNESS );
  //save_brightness(BRIGHTNESS);
  //cycle_steps = 25 * CYCLE_THROUGH - BRIGHTNESS;
  //Serial.println("Changed brightness to:");
  //Serial.println(BRIGHTNESS);
}

int get_led_brightness() {
  //Serial.println(BRIGHTNESS);
  return BRIGHTNESS;
}

int get_led_speed() {
  //Serial.println(RATE);
  return RATE;
}

void set_led_speed(int new_speed) {
  RATE = new_speed;
  save_speed(RATE);
}

int get_led_cycle() {
  //Serial.println(CYCLE_THROUGH);
  return CYCLE_THROUGH;
}

void set_led_cycle(int new_cycle) {
  CYCLE_THROUGH = new_cycle;
  save_cycle_time(CYCLE_THROUGH);
  cycle_steps = 25 * CYCLE_THROUGH - BRIGHTNESS;
}

void next_anim() {
  if (animation_mode < max_anim) {
    animation_mode++;
  } else {
    animation_mode = 0;
  }
  save_animation();
  //display_animation_mode();

  state_changed = true;
}

void prev_anim() {
  if (animation_mode > 0) {
    animation_mode--;
  }
  else {
    animation_mode = max_anim;
  }
  save_animation();
  //display_animation_mode();

  state_changed = true;
}
//ANIMATIONS HERE

///////////////////////////NOT ANYMORE, BEEATCH! PLEASE VISIT "Animation.h" for more info

//ANIMATIONS HEHE


int button_counter = 0;
//int repeated_press = 0;



void button_press(int time_pressed) {
  //if (time_pressed > 10) {
  Serial.println(time_pressed);
  //}
  if (time_pressed > 5 && time_pressed < 30) {
    anim_play = !anim_play; //play or pause
    //next_anim();
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

void generate_sequence() {
  int anim_aux[max_anim - 2];
  for (int i = 2; i < max_anim; i++) {
    anim_aux[i - 2] = i;
  }
  for (int i = 0; i < max_anim - 2; i++) {
    int test_case = random(0, (max_anim - 2));
    if (i > 0) {
      while (anim_aux[test_case] == 0) {
        test_case = random(0, (max_anim - 2));
      }
    }
    anim_sequence[i] = anim_aux[test_case];
    //Serial.println(anim_aux[test_case]);
    anim_aux[test_case] = 0;

  }
}

int led_ck = 0;
int button_ck = 0;
int cycle_counter = 0;
int bright_counter = 0;
uint8_t _rate = 100 - RATE;
int random_counter = 0;


int local_anim_mode = 2;
void do_anim(int which_one) {
  switch (which_one) {
    case 0://OFF
      fadeall();
      break;
    case 1://CYCLE THROUGH MODES
      if (fade_in && step_counter < BRIGHTNESS) {//Fade in
        FastLED.setBrightness(step_counter);
        //Serial.println(step_counter);//0-255
      }
      if (fade_out && step_counter >= cycle_steps) {//Fade out
        bright_counter++;
        int birt = BRIGHTNESS - bright_counter; //In loving memory of Birt Sampson
        FastLED.setBrightness(birt);
        if (birt <= 1)state_changed = true;
        //Serial.println(birt);
      }
      step_counter++;

      if (millis() >= cycle_counter + CYCLE_THROUGH * 1000) {
        cycle_counter = millis();
        if (random_counter < max_anim - 2) {
          random_counter++;
        } else {
          random_counter = 0;
          generate_sequence();
        }
        local_anim_mode = anim_sequence[random_counter];
        //        if (local_anim_mode < max_anim) {
        //          local_anim_mode++;
        //        } else {
        //          local_anim_mode = 2;
        //        }
        //Serial.println(step_counter);
        step_counter = 0;
        bright_counter = 0;
      }
      do_anim(local_anim_mode);//Recursion, BI4TCH!1

      break;
    case 2:
      Ocean();
      break;
    case 3:
      TwinkleFox();
      break;
    case 4:
      pride();
      break;
      //        case 5:
      //          Palette();
      //          break;
  }
  if (which_one > 4 && which_one < max_anim) {
    if (state_changed) {
      int palette_index = which_one - 5;
      Palette(palette_index);
      state_changed = false;
    }
    Palette();
  }
}

String get_animation_name() {
  String answer = "";
  if (animation_mode == 1) {
    answer += "CYCLE: " + animation_names[local_anim_mode];
  }
  else {
    answer += animation_names[animation_mode];
  }
  return answer;
}


void led_loop() {
  if (anim_play) {
    if (millis() >= led_ck + _rate) {
      led_ck = millis();

      do_anim(animation_mode);

      FastLED.show();
    }
  }

  if (millis() >= button_ck + BUTTON_RATE) {
    button_ck = millis();
    button_loop();
  }
}
