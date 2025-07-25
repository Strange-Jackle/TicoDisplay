#include <Arduino.h>
#include <unity.h>
#include "DisplayClient.h"
#include "DisplayClient.cpp"

// Mock Serial1
class MockStream : public Stream {
public:
    String written_data;
    size_t write(uint8_t) override { return 1; }
    size_t write(const uint8_t *buffer, size_t size) override {
        written_data = String((char*)buffer);
        return size;
    }
    int available() override { return 0; }
    int read() override { return 0; }
    int peek() override { return 0; }
    void flush() override {}
};

MockStream mock_serial;
#define Serial1 mock_serial

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_fillScreen() {
    DisplayClient display;
    display.fillScreen("BLUE");
    TEST_ASSERT_EQUAL_STRING("FILL,BLUE\n", mock_serial.written_data.c_str());
}

void test_drawText() {
    DisplayClient display;
    display.drawText(10, 20, "Hello");
    TEST_ASSERT_EQUAL_STRING("DRAW_TEXT,10,20,Hello\n", mock_serial.written_data.c_str());
}

void test_drawRect() {
    DisplayClient display;
    display.drawRect(5, 5, 50, 50, "RED");
    TEST_ASSERT_EQUAL_STRING("DRAW_RECT,5,5,50,50,RED\n", mock_serial.written_data.c_str());
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_fillScreen);
    RUN_TEST(test_drawText);
    RUN_TEST(test_drawRect);
    UNITY_END();
}

void loop() {
}
