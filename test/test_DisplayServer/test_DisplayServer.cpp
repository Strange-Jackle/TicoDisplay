#include <Arduino.h>
#include <unity.h>
#include "DisplayServer.h"
#include "TFT_eSPI.h"

// Mock TFT_eSPI
class MockTFT : public TFT_eSPI {
public:
    String last_string;
    int16_t last_x;
    int16_t last_y;
    int16_t last_w;
    int16_t last_h;
    uint16_t last_color;

    void fillScreen(uint16_t color) override {
        last_color = color;
    }

    void drawString(const char *string, int16_t x, int16_t y) override {
        last_string = string;
        last_x = x;
        last_y = y;
    }

    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
        last_x = x;
        last_y = y;
        last_w = w;
        last_h = h;
        last_color = color;
    }
};

MockTFT tft;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_parseColor() {
    DisplayServer server;
    TEST_ASSERT_EQUAL_UINT16(TFT_BLACK, server.parseColor("BLACK"));
    TEST_ASSERT_EQUAL_UINT16(TFT_WHITE, server.parseColor("WHITE"));
    TEST_ASSERT_EQUAL_UINT16(TFT_RED, server.parseColor("RED"));
    TEST_ASSERT_EQUAL_UINT16(0x1234, server.parseColor("0x1234"));
    TEST_ASSERT_EQUAL_UINT16(TFT_WHITE, server.parseColor("INVALID"));
}

void test_processCommand_fill() {
    DisplayServer server;
    server.processCommand("FILL,BLUE");
    TEST_ASSERT_EQUAL_UINT16(TFT_BLUE, tft.last_color);
}

void test_processCommand_drawText() {
    DisplayServer server;
    server.processCommand("DRAW_TEXT,10,20,Hello");
    TEST_ASSERT_EQUAL_STRING("Hello", tft.last_string.c_str());
    TEST_ASSERT_EQUAL_INT16(10, tft.last_x);
    TEST_ASSERT_EQUAL_INT16(20, tft.last_y);
}

void test_processCommand_drawRect() {
    DisplayServer server;
    server.processCommand("DRAW_RECT,5,5,50,50,RED");
    TEST_ASSERT_EQUAL_INT16(5, tft.last_x);
    TEST_ASSERT_EQUAL_INT16(5, tft.last_y);
    TEST_ASSERT_EQUAL_INT16(50, tft.last_w);
    TEST_ASSERT_EQUAL_INT16(50, tft.last_h);
    TEST_ASSERT_EQUAL_UINT16(TFT_RED, tft.last_color);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_parseColor);
    RUN_TEST(test_processCommand_fill);
    RUN_TEST(test_processCommand_drawText);
    RUN_TEST(test_processCommand_drawRect);
    UNITY_END();
}

void loop() {
}
