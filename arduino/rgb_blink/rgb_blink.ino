/*
  © 2023 Wendee Hsu. All rights reserved.
  Filename: rgb_blink.ino
  Goal: Blink for 8 different colors.
*/
void setup() {
  // put your setup code  here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      for(int k = 0; k < 2; k++) {
        Serial.println(i + " " + j + " " + k);
      }
    }
  }
}

void loop() {
  // as HIGH = 1, LOW = 0, I use 3 for loops to control each color light
  // 2**3 = 8 will be the final color combinations in the end.
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      for(int k = 0; k < 2; k++) {
        Serial.println(i + " " + j + " " + k);
        digitalWrite(LEDR, i);
        digitalWrite(LEDG, j);
        digitalWrite(LEDB, k);
        delay(1000);
      }
    }
  }
}
