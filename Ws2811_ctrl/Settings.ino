#include <EEPROM.h>
//EEPROM MAP
#define TIMED_ON 0
#define TIMED_FADE 1
#define GMT 2
#define DST 3
#define ON_TIME 4
#define OFF_TIME 6

int h_on, m_on, h_off, m_off;
String on_time, off_time;
void load_settings() {
  read_time();
}

void save_time(int H_ON, int M_ON, int H_OFF, int M_OFF) {
  //Serial.println(H_ON);
  //Serial.println(M_ON);
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
  on_time=h_on + ":" + m_on;
  off_time=h_off + ":" + m_off;
  
  EEPROM.end(); 
}

String get_on_time() {
  return on_time;
}

String get_off_time() {
  return off_time;
}
