#ifdef ARDUINO_ARCH_ESP32
#include "DisplayClient.h"

// ESP32-C3 remaps RX1=GPIO6, TX1=GPIO7
void DisplayClient::begin() {
  Serial1.begin(115200, SERIAL_8N1, 6 /*RX*/, 7 /*TX*/);
}

static bool sendCmd(const char* cmd) {
  return Serial1.println(cmd) > 0;
}

bool DisplayClient::fillScreen(const char* color) {
  char cmd[64];
  snprintf(cmd, sizeof(cmd), "FILL,%s", color);
  return sendCmd(cmd);
}

bool DisplayClient::drawText(int x, int y, const char* txt) {
  char cmd[256];
  snprintf(cmd, sizeof(cmd), "DRAW_TEXT,%d,%d,%s", x, y, txt);
  return sendCmd(cmd);
}

bool DisplayClient::drawRect(int x, int y, int w, int h, const char* color) {
  char cmd[128];
  snprintf(cmd, sizeof(cmd), "DRAW_RECT,%d,%d,%d,%d,%s", x, y, w, h, color);
  return sendCmd(cmd);
}
#endif  // ARDUINO_ARCH_ESP32
