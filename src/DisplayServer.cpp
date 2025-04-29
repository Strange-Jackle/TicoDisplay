#ifdef ARDUINO_ARCH_RP2040
#include "DisplayServer.h"

static TFT_eSPI tft;

void DisplayServer::begin() {
  // Power & backlight
  pinMode(PIN_PWR_ON, OUTPUT);
  digitalWrite(PIN_PWR_ON, HIGH);
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);

  // UART2 ↔ ESP32 at 38400 baud
  Serial2.setTX(ESP32C3_TX_PIN);
  Serial2.setRX(ESP32C3_RX_PIN);
  Serial2.begin(38400);

  // Initialize display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void DisplayServer::handle() {
  if (Serial2.available()) {
    String cmd = Serial2.readStringUntil('\n');
    cmd.trim();                        // trim() returns void :contentReference[oaicite:4]{index=4}
    processCommand(cmd);
  }
}

void DisplayServer::processCommand(const String& cmd) {
  int p = cmd.indexOf(',');
  String key = cmd.substring(0, p);
  String args = (p > 0 ? cmd.substring(p + 1) : "");

  if      (key == "FILL") {
    tft.fillScreen(parseColor(args));
  }
  else if (key == "DRAW_TEXT") {
    int c1 = args.indexOf(','), c2 = args.indexOf(',', c1 + 1);
    int x = args.substring(0, c1).toInt();
    int y = args.substring(c1+1, c2).toInt();
    String txt = args.substring(c2 + 1);
    tft.drawString(txt.c_str(), x, y);
  }
  else if (key == "DRAW_RECT") {
    int c1 = args.indexOf(','), c2 = args.indexOf(',', c1 + 1);
    int c3 = args.indexOf(',', c2 + 1), c4 = args.indexOf(',', c3 + 1);
    int x = args.substring(0, c1).toInt();
    int y = args.substring(c1+1, c2).toInt();
    int w = args.substring(c2+1, c3).toInt();
    int h = args.substring(c3+1, c4).toInt();
    uint16_t col = parseColor(args.substring(c4 + 1));
    tft.drawRect(x, y, w, h, col);
  }
  // …add more commands here…
}

uint16_t DisplayServer::parseColor(const String& s) {
  if (s == "BLACK") return TFT_BLACK;
  if (s == "WHITE") return TFT_WHITE;
  if (s == "RED")   return TFT_RED;
  if (s.startsWith("0x"))
    return (uint16_t)strtol(s.c_str(), nullptr, 16);
  return TFT_WHITE;
}
#endif  // ARDUINO_ARCH_RP2040
