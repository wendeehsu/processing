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
  // put your main code here, to run repeatedly:

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
