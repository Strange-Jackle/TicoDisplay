#include <DisplayServer.h>

#ifdef ARDUINO_ARCH_RP2040
DisplayServer server;

void setup() {
  server.begin();
}

void loop() {
  server.handle();
}
#endif
