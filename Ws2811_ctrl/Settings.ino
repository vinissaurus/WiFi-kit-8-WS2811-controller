#include <EEPROM.h>
#include <NTPClient.h>//https://github.com/arduino-libraries/NTPClient
#include <WiFiUdp.h>
#define EE_SIZE 512
#define TIME_UPDATE_RATE 5000//ms
//#define FADE_MINUTES 10 //might convert to a variable, if needed to user config (deprecated)
//EEPROM MAP
#define TIMED_ON 0
#define TIMED_FADE 1
#define GMT 2
#define DST 3
#define ON_TIME 4
#define OFF_TIME 6
#define ANIMATION 8
#define BRIGHTNESS 9
#define SPEED 10
#define CYCLE_TIME 11
#define CREDENTIALS_SLOT 12



uint8_t h_on, m_on, h_off, m_off;
uint8_t h_off_F, m_off_F;
uint16_t on_time, off_time;
bool time_schedule;
uint8_t fade_settings;
uint8_t bright_settings;
int hour_offset = 0;
uint8_t time_brightness = 0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void load_settings() {
  EEPROM.begin(EE_SIZE);
  time_schedule = (EEPROM.read(TIMED_ON) == 1 ? true : false);
  fade_settings = EEPROM.read(TIMED_FADE);
  set_led_fade(fade_settings);
  hour_offset = EEPROM.read(GMT) - 12;
  //LINE Reserved for DST
  read_time();//ON_TIME & OFF_TIME
  animation_mode = EEPROM.read(ANIMATION);
  bright_settings = EEPROM.read(BRIGHTNESS);
  //bright_settings = 500;//just for the debug-------------------------------------------------
  set_led_brightness(bright_settings);
  set_led_speed(EEPROM.read(SPEED));
  set_led_cycle(EEPROM.read(CYCLE_TIME));

  if (time_schedule) {
    timeClient.begin();
    timeClient.update();
    int t_offset = hour_offset * 3600;
    timeClient.setTimeOffset(t_offset);
    update_fading_time();
  }
}

void update_fading_time() {//update the time for starting to fade out
  if (fade_settings != 0) {
    time_brightness = 1;
    h_off_F = h_off;
    m_off_F = m_off - ((bright_settings * 5) - (bright_settings * 5) % 60) / 60;
    if (m_off_F < 0) {//in case this variable is a negative number, which means the starting hour for the fade is on hour earlier
      h_off_F = h_off - 1; //subtract an hour
      m_off_F += 60;//correct the difference
    }
    if (timeClient.getHours() > h_on || (timeClient.getHours() == h_on && timeClient.getMinutes() > m_on + 20)) {
      time_brightness = bright_settings;
    }
  }
  //Serial.println("---");
  //  Serial.print("h_off_F="); Serial.print(h_off_F); Serial.println("---");
  //  Serial.print("m_off_F="); Serial.print(m_off_F); Serial.println("---\n");
  //Serial.println("---");
}

int get_animation_mode() {
  EEPROM.begin(EE_SIZE);
  return EEPROM.read(ANIMATION);
}

void save_time_schedule(bool ts) {
  time_schedule = ts;
  EEPROM.begin(EE_SIZE);
  if (time_schedule) {
    EEPROM.write(TIMED_ON, 1);
  } else {
    EEPROM.write(TIMED_ON, 0);
    set_led_brightness_d(bright_settings);
  }
  EEPROM.commit();
  update_fading_time();
  //Serial.println(EEPROM.read(TIMED_ON));
  //EEPROM.end();
}

bool get_time_schedule() {
  return time_schedule;
}

bool STATE_ON = false;
int timed_loop_ck = 0;

void timed_schedule_loop() {
  if (time_schedule) {
    if (millis() >= timed_loop_ck + TIME_UPDATE_RATE) {
      timed_loop_ck = millis();
      timeClient.update();
      int now_H = timeClient.getHours();
      int now_M = timeClient.getMinutes();
      int now_S = timeClient.getSeconds();

      if (fade_settings == 1 || fade_settings == 3) { //Fade in enabled--> set_led_brightness_d(int new_brightness)
        if (now_H == h_on && now_M >= m_on && time_brightness < bright_settings) {
          time_brightness = (now_M - m_on) * 12 + (now_S - now_S % 5) / 5;
          set_led_brightness_d(time_brightness);
          //          Serial.println();
          //          Serial.print(now_S);
          //          Serial.print("-ON->");
          //          Serial.print(time_brightness);
          //
        }
      }
      if ((fade_settings == 2 || fade_settings == 3) && time_brightness > 0) { //Fade out enabled
        if (now_H == h_off_F && now_M >= m_off_F) {//n
          time_brightness = bright_settings - ((now_M - m_off_F) * 12 + (now_S - now_S % 5) / 5);
          set_led_brightness_d(time_brightness);
        }
        if (now_H == h_off && now_M <= m_off && h_off_F == h_off - 1) { //now_H == h_off && now_M < m_off

          time_brightness = bright_settings - ((now_M  + 60 - m_off_F) * 12 + (now_S - now_S % 5) / 5);
          //int rst = now_M  - 60 - m_off_F;
          //Serial.println("Dos");
          //          Serial.println(rst);
          set_led_brightness_d(time_brightness);
        }
        //        if (now_H == h_off && now_M <= m_off) {//now_H == h_off && now_M < m_off
        //          time_brightness = bright_settings - ((now_M  - m_off) * 12 + (now_S - now_S % 5) / 5);
        //          //set_led_brightness_d(time_brightness);
        //          Serial.println("Dos");
        //          Serial.println(rst);
        //        }

        //        Serial.println();
        //        Serial.print(now_S);
        //        Serial.print("-OFF->");
        //        Serial.print(time_brightness);
      }

      if (fade_settings == 0) { //if fade in/out disabled
        if ((now_H == h_on && now_M >= m_on) || (now_H == h_off && now_M <= m_off)) {
          animation_state(true);
          //Serial.println("I'm on, B1TCH");
        } else if (h_on <= h_off && (now_H > h_on && now_H < h_off) ) {
          animation_state(true);
          //Serial.println("I'm on, B1TCH");
        } else if (h_on > h_off && (now_H > h_on && now_H > h_off)) {
          animation_state(true);
          //Serial.println("I'm on, B1TCH");
        } else {
          animation_state(false);
          //Serial.println("I'm ofF");
        }
      }

    }
  }
}

void save_time(int H_ON, int M_ON, int H_OFF, int M_OFF) {
  //Serial.println(H_ON);
  //Serial.println(M_ON);
  h_on = H_ON;
  m_on = M_ON;
  h_off = H_OFF;
  m_off = M_OFF;
  EEPROM.begin(EE_SIZE);
  EEPROM.write(ON_TIME, H_ON);
  EEPROM.write(ON_TIME + 1, M_ON);
  EEPROM.write(OFF_TIME, H_OFF);
  EEPROM.write(OFF_TIME + 1, M_OFF);
  EEPROM.commit();
  //EEPROM.end();
  update_fading_time();
}

void read_time() {
  //EEPROM.begin(EE_SIZE);
  h_on = EEPROM.read(ON_TIME);
  m_on = EEPROM.read(ON_TIME + 1);
  h_off = EEPROM.read(OFF_TIME);
  m_off = EEPROM.read(OFF_TIME + 1);
  on_time = h_on * 100 + m_on;
  off_time = h_off * 100 +  m_off;
  //EEPROM.end();
}

void save_animation() {
  EEPROM.begin(EE_SIZE);
  EEPROM.write(ANIMATION, animation_mode);
  EEPROM.commit();
  //EEPROM.end();
}



void save_brightness(int new_brighness) {
  bright_settings = new_brighness;
  EEPROM.begin(EE_SIZE);
  EEPROM.write(BRIGHTNESS, new_brighness);
  EEPROM.commit();
  //EEPROM.end();
  update_fading_time();
}

void save_speed(int new_speed) {
  EEPROM.begin(EE_SIZE);
  EEPROM.write(SPEED, new_speed);
  EEPROM.commit();
  //EEPROM.end();
  //Serial.println(EEPROM.read(SPEED));
}

void save_cycle_time(int new_cycle_time) {
  EEPROM.begin(EE_SIZE);
  EEPROM.write(CYCLE_TIME, new_cycle_time);
  EEPROM.commit();
  //EEPROM.end();
  //Serial.println(EEPROM.read(CYCLE_TIME));
}


void save_fade_settings(int new_settings) {
  fade_settings = new_settings;
  EEPROM.begin(EE_SIZE);
  EEPROM.write(TIMED_FADE , new_settings);
  //Serial.println(EEPROM.read(TIMED_FADE));
  EEPROM.commit();
  if (new_settings == 0) {
    set_led_brightness_d(bright_settings);
  }
  update_fading_time();
}


int get_on_time() {
  on_time = h_on * 100 + m_on;
  return on_time;
}

int get_off_time() {
  off_time = h_off * 100 +  m_off;
  return off_time;
}


int get_timezone() {
  return hour_offset;
}



void set_timezone(int new_timezone) {
  hour_offset = new_timezone;
  int corrected_tz = 12 + new_timezone;
  EEPROM.begin(EE_SIZE);
  EEPROM.write(GMT , corrected_tz);
  EEPROM.commit();
  int t_offset = hour_offset * 3600;
  timeClient.setTimeOffset(t_offset);
  timeClient.forceUpdate();
  update_fading_time();
}

void save_credentials() {
  EEPROM.begin(EE_SIZE);
  //salvar o tamanho do SSID:
  EEPROM.write(CREDENTIALS_SLOT, memSSID.length());
  int starting = CREDENTIALS_SLOT + 1;
  //salvar o SSID
  for (int i = 0; i < memSSID.length(); ++i) {
    EEPROM.write(starting + i, memSSID[i]);
    // Serial.print(memSSID[i]);
  }
  //Serial.println("----testcase1");


  starting = CREDENTIALS_SLOT + 1 + memSSID.length() + 1;
  //salvar o tamanho da senha
  EEPROM.write(CREDENTIALS_SLOT + 1 + memSSID.length(), memPSK.length());
  //salvar la seña
  for (int i = 0; i < memPSK.length(); ++i) {
    EEPROM.write(starting + i, memPSK[i]);
    //Serial.print(memPSK[i]);
  }
  //Serial.println("----testcase2");
  EEPROM.commit();
  //EEPROM.end();
}


void load_credentials() {
  //ler o tamanho do SSID
  memSSID = "";
  memPSK = "";
  EEPROM.begin(EE_SIZE);
  int sizeOf = EEPROM.read(CREDENTIALS_SLOT);
  if (sizeOf == 0) {//verificar se existem credenciais registradas
    memPSK = "@null";
    //Serial.println("IsNull");

  }
  else {
    int starting = CREDENTIALS_SLOT + 1;
    //ler o SSID
    for (int i = 0; i < sizeOf; ++i) {
      memSSID += char(EEPROM.read(starting + i));
    }
    //Serial.println(memSSID);
    //ler o tamanho do PSK
    starting = CREDENTIALS_SLOT + 1 + memSSID.length() + 1;
    sizeOf = EEPROM.read(CREDENTIALS_SLOT + 1 + memSSID.length());
    for (int i = 0; i < sizeOf; ++i)  {
      memPSK += char(EEPROM.read(starting + i));
    }
  }
  //Serial.println(memPSK);
  //EEPROM.end();

}

void delete_credentials() {
  Serial.println("Deleting credentials...");
  EEPROM.begin(EE_SIZE);
  EEPROM.write(CREDENTIALS_SLOT, 0);
  EEPROM.commit();
  //EEPROM.end();
}
