<h2>WS2811-Control</h2>
This is a simple controller for a WS2811LED strip, which features:
-A captive portal to set up a wifi connection 
![captive_portal](https://user-images.githubusercontent.com/18562403/144535154-418e3daf-8c1e-4091-b537-dea1c2ed8b80.JPG)

-A UI that you can reach through your network wesp2811.local (you can change to other name in the code)
![web_ui](https://user-images.githubusercontent.com/18562403/144534986-3f279588-1085-4e45-aa01-7f3fa575b4d6.JPG)

And some animations for the LED strip, which were all from FastLED's examples.

**Libraries used:**<br>
//#include <U8g2lib.h>//<sub>There is not enough RAM in an ESP8266 to handle a small OLED display with all the other functions in this application. Did not test in and ESP32.</sub><br>
#include <FastLED.h>//https://github.com/FastLED/FastLED<br>
#include <ESPAsyncWebServer.h>//https://github.com/me-no-dev/ESPAsyncWebServer<br>
#include <ESPAsync_WiFiManager.h>//https://github.com/khoih-prog/ESPAsync_WiFiManager<br>
#include <NTPClient.h>//https://github.com/arduino-libraries/NTPClient<br>
