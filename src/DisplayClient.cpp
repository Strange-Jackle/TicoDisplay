#ifdef ARDUINO_ARCH_ESP32
#include "DisplayClient.h"

// ESP32-C3 remaps RX1=GPIO6, TX1=GPIO7 :contentReference[oaicite:5]{index=5}
void DisplayClient::begin() {
  Serial1.begin(38400, SERIAL_8N1, 6 /*RX*/, 7 /*TX*/);
}

static void sendCmd(const String& cmd) {
  Serial1.println(cmd);
}

void DisplayClient::fillScreen(const char* color) {
  sendCmd(String("FILL,") + color);
}

void DisplayClient::drawText(int x, int y, const char* txt) {
  sendCmd(String("DRAW_TEXT,") + x + "," + y + "," + txt);
}

void DisplayClient::drawRect(int x, int y, int w, int h, const char* color) {
  sendCmd(String("DRAW_RECT,") + x + "," + y + "," + w + "," + h + "," + color);
}
#endif  // ARDUINO_ARCH_ESP32
