#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <U8g2lib.h> // u8g2 library for drawing on OLED display - needs to be installed in Arduino IDE first
#include <Wire.h> // wire library for IIC communication with the OLED display
#include "konoha.h"
#include "sand.h"
#include "audio.h"
#include "union.h"

// LED ring
#define PIN 6
#define PIN_s 4
#define LIGHT_NUM_L 24
#define LIGHT_NUM_S 16
#define FRAME_SIZE 128

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LIGHT_NUM_L, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_s = Adafruit_NeoPixel(LIGHT_NUM_S, PIN_s, NEO_GRB + NEO_KHZ800);

const int buttonPin = 2;     // THIS IS THE VAlUE YOU COULD CHANGE TO 3
int buttonState = 0;         // variable for reading the pushbutton status
int rainbow_color = 1;
int lights[LIGHT_NUM_L];
int lights_s[LIGHT_NUM_S];
bool hasBlink = false;
int reds[4] = {40, 235, 255, 191};
int greens[4] = {211, 64, 198, 28};
int blues[4] = {255, 52, 28, 255};

// OLED
U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int oled_mark = 3;

void setup(void) {
  // RGB Ring
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  strip_s.begin();
  strip_s.setBrightness(50);
  strip_s.show(); // Initialize all pixels to 'off'
  pinMode(buttonPin, INPUT);

  for (int i = 0; i < LIGHT_NUM_L; i++) {
    lights[i] = i;
  }

  for (int i = 0; i < LIGHT_NUM_S; i++) {
    lights_s[i] = LIGHT_NUM_S - i -1;
  }

  // OLED
  u8g2.begin();  // begin the u8g2 library
  u8g2.setContrast(255); // set display contrast/brightness
}

void loop(void) {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && !hasBlink) {
    // turn off the small ring
    for (int i = 0; i < LIGHT_NUM_S; i++) {
      strip_s.setPixelColor(lights_s[i], 0,0,0);
    }
    strip_s.show();

    // blink the large ring
    for (int i = 0; i < 10; i++) {
      blink(30);
    }
    hasBlink = true;
    
    oled_mark += 1;
    if (oled_mark > 3) {
      oled_mark = 0;
    }
    updateOLED();
  }

  if (buttonState == LOW) {
      cycle(30);
  } else {
    hasBlink = false;
  }
}

void updateOLED() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(false /* solid */);
  u8g2.setDrawColor(0);// Black
  if (oled_mark == 1) {
    u8g2.drawXBMP(0, 0, FRAME_SIZE, FRAME_SIZE, unions);
  } else if (oled_mark == 2) {
    u8g2.drawXBMP(0, 0, FRAME_SIZE, FRAME_SIZE, sand);
  } else if (oled_mark == 3) {
    u8g2.drawXBMP(0, 0, FRAME_SIZE, FRAME_SIZE, audio);
  } else {
    u8g2.drawXBMP(0, 0, FRAME_SIZE, FRAME_SIZE, konoha);
  }
  u8g2.sendBuffer();
}

void blink(int wait) {
  int r = random(10,255);
  int g = random(10,255);
  int b = random(10,255);
  for(uint16_t i=0; i<LIGHT_NUM_L; i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
  delay(wait+5);

  for(uint16_t i=0; i<LIGHT_NUM_L; i++) {
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
  delay(wait);
}

void cycle(int wait) {
  // large ring
  int r = reds[oled_mark];
  int g = greens[oled_mark];
  int b = blues[oled_mark];

  int gap = LIGHT_NUM_L/2;
  for (int i = 0; i < LIGHT_NUM_L/2; i++) {
    strip.setPixelColor(lights[i], r - i * r/gap, g - i * g/gap, b - i * b/gap);
  }

  for (int i = LIGHT_NUM_L/2; i < LIGHT_NUM_L; i++) {
    strip.setPixelColor(lights[i], 0,0,0);
  }
  strip.show();

  // small ring
  int gap_s = strip_s.numPixels()/2;
  for (int i = 0; i < strip_s.numPixels()/2; i++) {
    strip_s.setPixelColor(lights_s[i], 255 - i * 255/gap_s, 255 - i * 255/gap_s, 255 - i * 255/gap_s);
  }

  for (int i = strip_s.numPixels()/2; i < strip_s.numPixels(); i++) {
    strip_s.setPixelColor(lights_s[i], 0,0,0);
  }
  strip_s.show();

  delay(wait);

  // update large lights
  int tmp = lights[0];
  for (int i = 0; i < LIGHT_NUM_L-1; i++) {
    lights[i] = lights[i+1];
  }
  lights[LIGHT_NUM_L-1] = tmp;

   // update small lights
  int tmp_s = lights_s[0];
  for (int i = 0; i < strip_s.numPixels()-1; i++) {
    lights_s[i] = lights_s[i+1];
  }
  lights_s[strip_s.numPixels()-1] = tmp_s;
}
