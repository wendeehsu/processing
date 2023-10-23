#include <Arduino.h>
#include <U8g2lib.h> // u8g2 library for drawing on OLED display - needs to be installed in Arduino IDE first
#include <Wire.h> // wire library for IIC communication with the OLED display
#include "konoha.h"
#include "sand.h"
#include "audio.h"
#include "union.h"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int mark = 0;

void setup(void) { // Arduino setup
  u8g2.begin();  // begin the u8g2 library
  u8g2.setContrast(255); // set display contrast/brightness
}

void loop(void) { // main Arduino loop
  u8g2.clearBuffer();
  int frame_size = 128;
  u8g2.setBitmapMode(false /* solid */);
  u8g2.setDrawColor(0);// Black
  if (mark == 1) {
    u8g2.drawXBMP(0, 0, frame_size, frame_size, unions);
  } else if (mark == 2) {
    u8g2.drawXBMP(0, 0, frame_size, frame_size, sand);
  } else if (mark == 3) {
    u8g2.drawXBMP(0, 0, frame_size, frame_size, audio);
  } else {
    u8g2.drawXBMP(0, 0, frame_size, frame_size, konoha);
  }
  u8g2.sendBuffer();
  
  mark += 1;
  if (mark > 3) {
    mark = 0;
  }
  delay(3000);
}
