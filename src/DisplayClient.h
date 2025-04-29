#pragma once
#include <Arduino.h>
#include "pin_config.h"

#ifdef ARDUINO_ARCH_ESP32
class DisplayClient {
public:
  void begin();
  void fillScreen(const char* color);
  void drawText(int x, int y, const char* txt);
  void drawRect(int x, int y, int w, int h, const char* color);
};
#endif  // ARDUINO_ARCH_ESP32
