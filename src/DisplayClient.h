#pragma once
#include <Arduino.h>
#include "pin_config.h"

#ifdef ARDUINO_ARCH_ESP32
class DisplayClient {
public:
  void begin();
  bool fillScreen(const char* color);
  bool drawText(int x, int y, const char* txt);
  bool drawRect(int x, int y, int w, int h, const char* color);
};
#endif  // ARDUINO_ARCH_ESP32
