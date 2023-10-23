#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define PIN_s 4
#define LIGHT_NUM_L 24
#define LIGHT_NUM_S 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LIGHT_NUM_L, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_s = Adafruit_NeoPixel(LIGHT_NUM_S, PIN_s, NEO_GRB + NEO_KHZ800);

const int buttonPin = 2;     // THIS IS THE VAlUE YOU COULD CHANGE TO 3
int buttonState = 0;         // variable for reading the pushbutton status
int rainbow_color = 1;
int lights[LIGHT_NUM_L];
int lights_s[LIGHT_NUM_S];
bool hasBlink = false;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  strip_s.begin();
  strip_s.setBrightness(50);
  strip_s.show(); // Initialize all pixels to 'off'
  pinMode(buttonPin, INPUT);

  for (int i = 0; i < strip.numPixels(); i++) {
    lights[i] = i;
  }

  for (int i = 0; i < LIGHT_NUM_S; i++) {
    lights_s[i] = LIGHT_NUM_S - i -1;
  }
}

void loop() {
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
  }

  if (buttonState == LOW) {
      cycle(30);
  } else {
    hasBlink = false;
  }
}

void blink(int wait) {
  int r = random(10,255);
  int g = random(10,255);
  int b = random(10,255);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
  delay(wait+5);

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
  delay(wait);
}

void cycle(int wait) {
  // large ring
  int gap = strip.numPixels()/2;
  for (int i = 0; i < strip.numPixels()/2; i++) {
    strip.setPixelColor(lights[i], 40 - i * 40/gap, 211 - i * 211/gap, 255 - i * 255/gap);
  }

  for (int i = strip.numPixels()/2; i < strip.numPixels(); i++) {
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
  for (int i = 0; i < strip.numPixels()-1; i++) {
    lights[i] = lights[i+1];
  }
  lights[strip.numPixels()-1] = tmp;

   // update small lights
  int tmp_s = lights_s[0];
  for (int i = 0; i < strip_s.numPixels()-1; i++) {
    lights_s[i] = lights_s[i+1];
  }
  lights_s[strip_s.numPixels()-1] = tmp_s;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait, int rainbow_color) {
  uint16_t i;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i+rainbow_color) & 255));
  }
  strip.show();
  delay(wait);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
