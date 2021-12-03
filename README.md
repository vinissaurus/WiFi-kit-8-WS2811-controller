<h2>WS2811-Control</h2>

This is a simple controller for a WS2811LED strip, which features:<br>
-A captive portal to set up a wifi connection<br> 
![captive](https://user-images.githubusercontent.com/18562403/144536800-d81c5d98-b185-4fd4-8ce7-1eb246ea7248.JPG)<br>

-A UI that you can reach through your network in the address http://wesp2811.local (you can change to other name in the code)<br>
![web_ui](https://user-images.githubusercontent.com/18562403/144534986-3f279588-1085-4e45-aa01-7f3fa575b4d6.JPG)<br>

And some animations for the LED strip, which were all from FastLED's examples.

**Libraries used:**<br>
//#include <U8g2lib.h>//<sub>There is not enough RAM in an ESP8266 to handle a small OLED display with all the other functions in this application. Did not test in and ESP32.</sub><br>
#include <FastLED.h>//https://github.com/FastLED/FastLED<br>
#include <ESPAsyncWebServer.h>//https://github.com/me-no-dev/ESPAsyncWebServer<br>
#include <ESPAsync_WiFiManager.h>//https://github.com/khoih-prog/ESPAsync_WiFiManager<br>
#include <NTPClient.h>//https://github.com/arduino-libraries/NTPClient<br>
