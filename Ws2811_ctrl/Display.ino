//OLEDDisplayUi ui     ( Heltec.display ); //128px X 32px
#include <U8g2lib.h>

int mainPage = 1;
int pageRate = 0;
unsigned long countZero = 0;
int steps = 1;
int stepCounter = 1;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C scr(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);
u8g2_uint_t offset;     // current offset for the scrolling text
u8g2_uint_t width;      // pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
const char *text = "VSSAURUS "; // scroll this text from right to left
const char *vers = "V 1.0";
const char *lastMod = "24/10/2019";
const char *title = "Ws2811 PIXCA";
char ipAdr[16];


void displayInit() {
 scr.begin();
  scr.setFont(u8g2_font_amstrad_cpc_extended_8f); // set the target font to calculate the pixel width
  width = scr.getUTF8Width(text);    // calculate the pixel width of the text
  scr.setFontMode(0);  
}


int clkTimer(int clocks = pageRate) { //timer para trocar as faces das páginas na tela OLED
  int currentMillis = millis();
  int timerOut = 0;
  if (countZero == 0) {
    countZero = currentMillis;
  }
  if (countZero + clocks <= currentMillis) {
    timerOut = 1;
    countZero = currentMillis;
    stepCounter++;
    timerOut = stepCounter;
    if (stepCounter > steps) {
      stepCounter = 1;
      timerOut = stepCounter;
    }

  }

  return timerOut;
}

void splashScreen() {
  //scr.firstPage();
  scr.clearDisplay();
  scr.setFont(u8g2_font_amstrad_cpc_extended_8f);
  scr.firstPage();
  do {
    scr.drawLine(0, 0, 127, 0);
    scr.drawLine(0, 31, 127, 31);
    scr.drawLine(0, 0, 0, 31);
    scr.drawLine(127, 0, 127, 31);

    scr.drawUTF8(4, 12, "Ws2811 PIXCA");
    scr.drawUTF8(4, 20, "by VSSAURUS");

  } while ( scr.nextPage() );
  delay(5000);
  scr.firstPage();
  do {
    scr.drawLine(0, 0, 127, 0);
    scr.drawLine(0, 31, 127, 31);
    scr.drawLine(0, 0, 0, 31);
    scr.drawLine(127, 0, 127, 31);

    scr.drawUTF8(4, 12, vers);
    scr.drawUTF8(4, 20, lastMod);

  } while ( scr.nextPage() );
  delay(5000);
}

void scrOut2(const char* a, const char* b) { //método para imprimir duas linhas na tela OLED
//  Heltec.display->clear();
//  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
//  Heltec.display->drawStringMaxWidth(4, 12,128, a);
//  Heltec.display->drawStringMaxWidth(4, 20,128, b);
//  Heltec.display->display();
  scr.firstPage();
  do {
    scr.drawUTF8(4, 12, a);
    scr.drawUTF8(4, 20, b);
  } while ( scr.nextPage() );
}

void scrMainPage(int c) {
  mainPage = c;
  switch (c) {
    case 1://wifi config page settings
      pageRate = 2000;
      steps = 5;
      break;
    case 2:

      break;

  }
}

void wifiConfigPage() {


}

void scr_setup(){
  scr.begin();
  scr.setFont(u8g2_font_amstrad_cpc_extended_8f); // set the target font to calculate the pixel width
  width = scr.getUTF8Width(text);    // calculate the pixel width of the text
  scr.setFontMode(0);    // enable transparent mode, which is faster
  splashScreen();

  do {
    scr.drawUTF8(4, 12, "Connected to:");
//    scr.drawUTF8(4, 20, ssid);

  } while ( scr.nextPage() );
  delay(2000);

  //sprintf(ipAdr,"",WiFi.localIP(),"");
  //sprintf(ipAdr, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  scr.firstPage();
  do {
    scr.drawUTF8(4, 12, "IP Address:");
    //scr.drawUTF8(4, 20, ipAdr);
    //scr.drawUTF8(4,20, "255.255.255.255");

  } while ( scr.nextPage() );

  scr.firstPage();
//  do {
//    scr.drawUTF8(4, 12, "Current time:");
//    scr.drawUTF8(4, 20, nowTime);
//  } while ( scr.nextPage() );
  }

void scr_loop() {
  //Heltec.display->clear();
   switch (mainPage) {
    case 1://WiFi config mode
      wifiConfigPage();
      break;
    case 2:
      break;
  }
  //scr.firstPage();
  //Heltec.display->display();
}
