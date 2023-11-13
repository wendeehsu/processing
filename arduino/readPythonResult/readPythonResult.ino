#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
const int MAX_MSG_LENGTH = 32;
char message[MAX_MSG_LENGTH];

void setup() {
  Serial.begin(9600);
  u8g2.begin();
}

void loop() {
  int availableBtyes = Serial.available();
  if (availableBtyes > 0) {
    // initMessage();

    // read new string
    for (int i = 0; i < availableBtyes; i++) {
      message[i] = Serial.read();
    }
    
    // Serial.println("received:"+msg);
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_iranian_sans_14_t_all);	// choose a suitable font
    u8g2.drawStr(0,10,message);	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display
    // delay(1000);
  }
}

void initMessage() {
  message[0] = '\0';
  // for (int i = 0; i < MAX_MSG_LENGTH; i++) {
  //   message[i] = '';
  // }
}
