#include <DisplayClient.h>

#ifdef ARDUINO_ARCH_ESP32
DisplayClient display;

void setup() {
  display.begin();
  delay(100);
  display.fillScreen("BLACK");
  display.drawText(20, 30, "Hello from ESP32!");
  display.drawRect(10, 10, 200, 100, "0xF800");
}

void loop() { }
#endif
