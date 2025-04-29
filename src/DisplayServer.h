#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pin_config.h"

#ifdef ARDUINO_ARCH_RP2040
class DisplayServer {
public:
  void begin();
  void handle();
private:
  void processCommand(const String& cmd);
  uint16_t parseColor(const String& s);
};
#endif  // ARDUINO_ARCH_RP2040
