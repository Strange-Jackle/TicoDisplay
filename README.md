
# TicoDisplay

Dual-core Display Control Library for Lilygo T-PicoC3


## Description

TicoDisplay is an Arduino library that enables the ESP32-C3 core on the Lilygo T-PicoC3 to drive its onboard TFT display via a serial (UART) link to the RP2040 core. The Lilygo T-PicoC3 is a dual-microcontroller board (ESP32-C3 + RP2040) with a built-in 1.14‑inch ST7789 TFT display​. TicoDisplay provides a simple API on the ESP32-C3 side to send graphics commands (text, shapes, colors, etc.) over UART; the RP2040 runs companion firmware (using the TFT_eSPI library) to update the display accordingly. This lets you use Wi-Fi and other ESP32 features without directly handling the display SPI bus.


## Features

- Dual-core display control: ESP32-C3 sends commands over UART to RP2040, which drives the ST7789 display.
- Graphics support: Draw pixels, lines, rectangles, text, and more in 16-bit color on the TFT.
- Transparent integration: Uses TFT_eSPI on the RP2040 (configured for the onboard 135×240 display​) while exposing a simpler interface to the ESP32.


## Installation

Make sure to have the TFT_eSPI library from the below which is compatiable with the Lilygo T-PicoC3 and also make sure the appropiate selection in User_Setup.h in TFT_eSPI is set up for the ST7789 display (135×240) as per Lilygo’s example​.

```bash
  https://github.com/Xinyuan-LilyGO/T-PicoC3/tree/main/lib/TFT_eSPI
```
Now download TicoDisplay as a .zip and add to your Arduino by using "Sketch->Include library->Add .ZIP Library" in Arduino IDE.

NOTE: You also need to install boards accordingly which can be done by searching "Pico" and "esp32" in the board manager.
## Usage/Examples

Here the RP2040 acts as the DisplaySever, you can open File → Examples → TicoDisplay → ServerDemo
```c++
#include <DisplayServer.h>

#ifdef ARDUINO_ARCH_RP2040
DisplayServer server;

void setup() {
  server.begin();
}

void loop() {
  server.handle();
}
```
And the ESP32-C3 acts as the Client, you can open File → Examples → TicoDisplay → ClientDemo
```c++
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
```
By Performing the above code you can see the output "Hello from ESP32!" on the TFT display which connected and controlled by RP2040.
## Feedback
There are still room for improvements and optimization.

If you have any feedback, please reach out at [Mail](mailto:thiskaranpatel@gmail.com)
Or Open [#Issue](https://github.com/Strange-Jackle/TicoDisplay/issues)


## 🔗 Links
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/strangejackle/)
[![twitter](https://img.shields.io/badge/twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://x.com/StrangeJackle)

