#include <EEPROM.h>
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

int h_on, m_on, h_off, m_off;
int on_time, off_time;

void load_settings() {
  read_time();

  EEPROM.begin(512);
  animation_mode = EEPROM.read(ANIMATION);
  //delay(200);
  set_led_brightness(EEPROM.read(BRIGHTNESS));
  //Serial.println(EEPROM.read(BRIGHTNESS));
  //delay(200);
  set_led_speed(EEPROM.read(SPEED));
  //Serial.println(EEPROM.read(SPEED));
  //delay(200);
  set_led_cycle(EEPROM.read(CYCLE_TIME));
  //Serial.println(EEPROM.read(CYCLE_TIME));
  //delay(200);
  //EEPROM.end();
  
}

void save_time(int H_ON, int M_ON, int H_OFF, int M_OFF) {
  //Serial.println(H_ON);
  //Serial.println(M_ON);
  h_on = H_ON;
  m_on = M_ON;
  h_off = H_OFF;
  m_off = M_OFF;
  EEPROM.begin(512);
  EEPROM.write(ON_TIME, H_ON);
  EEPROM.write(ON_TIME + 1, M_ON);
  EEPROM.write(OFF_TIME, H_OFF);
  EEPROM.write(OFF_TIME + 1, M_OFF);
  EEPROM.commit();
  //EEPROM.end();
}

void read_time() {
  EEPROM.begin(512);
  h_on = EEPROM.read(ON_TIME);
  m_on = EEPROM.read(ON_TIME + 1);
  h_off = EEPROM.read(OFF_TIME);
  m_off = EEPROM.read(OFF_TIME + 1);
  on_time = h_on * 100 + m_on;
  off_time = h_off * 100 +  m_off;

  //EEPROM.end();
}

void save_animation() {
  EEPROM.begin(512);
  EEPROM.write(ANIMATION, animation_mode);
  EEPROM.commit();
  //EEPROM.end();
}



void save_brightness(int new_brighness) {
  EEPROM.begin(512);
  EEPROM.write(BRIGHTNESS, new_brighness);
  EEPROM.commit();
  //EEPROM.end();
}

void save_speed(int new_speed) {
  EEPROM.begin(512);
  EEPROM.write(SPEED, new_speed);
  EEPROM.commit();
  //EEPROM.end();
}

void save_cycle_time(int new_cycle_time) {
  EEPROM.begin(512);
  EEPROM.write(CYCLE_TIME, new_cycle_time);
  EEPROM.commit();
  //EEPROM.end();
}

int get_on_time() {
  on_time = h_on * 100 + m_on;
  return on_time;
}

int get_off_time() {
  off_time = h_off * 100 +  m_off;
  return off_time;
}




void save_credentials() {
  EEPROM.begin(512);
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
  EEPROM.end();
}


void load_credentials() {
  //ler o tamanho do SSID
  memSSID = "";
  memPSK = "";
  EEPROM.begin(512);
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
  EEPROM.end();

}

void delete_credentials() {
  Serial.println("Deleting credentials...");
  EEPROM.begin(512);
  EEPROM.write(CREDENTIALS_SLOT, 0);
  EEPROM.commit();
  EEPROM.end();
}
