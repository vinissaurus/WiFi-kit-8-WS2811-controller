#include <EEPROM.h>
//EEPROM MAP
#define TIMED_ON 0
#define TIMED_FADE 1
#define GMT 2
#define DST 3
#define ON_TIME 4
#define OFF_TIME 6

int h_on, m_on, h_off, m_off;
int on_time, off_time;
void load_settings() {
  read_time();
}

void save_time(int H_ON, int M_ON, int H_OFF, int M_OFF) {
  //Serial.println(H_ON);
  //Serial.println(M_ON);
  h_on=H_ON;
  m_on=M_ON;
  h_off=H_OFF;
  m_off=M_OFF;
  EEPROM.begin(512);
  EEPROM.write(ON_TIME, H_ON);
  EEPROM.write(ON_TIME + 1, M_ON);
  EEPROM.write(OFF_TIME, H_OFF);
  EEPROM.write(OFF_TIME + 1, M_OFF);
  EEPROM.commit();
  EEPROM.end();
}

void read_time() {
  EEPROM.begin(512);
  h_on = EEPROM.read(ON_TIME);
  m_on = EEPROM.read(ON_TIME + 1);
  h_off = EEPROM.read(OFF_TIME);
  m_off = EEPROM.read(OFF_TIME + 1);
  on_time=h_on*100 + m_on;
  off_time=h_off*100 +  m_off;
  
  EEPROM.end(); 
}

int get_on_time() {
  on_time=h_on*100 + m_on;
  return on_time;
}

int get_off_time() {
  off_time=h_off*100 +  m_off;
  return off_time;
}
