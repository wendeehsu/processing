#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
const int MAX_MSG_LENGTH = 32;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
}

void loop() {

  // Reading code
  int availableBtyes = Serial.available();
  String message = "";
  if (availableBtyes > 0) {
    // TODO: break lines
    message = Serial.readString();

    // writing code
    u8g2.clearBuffer();  // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0, 10);
    u8g2.print(message);
    
    u8g2.sendBuffer(); 
  }
}
