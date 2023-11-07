#include <Arduino_APDS9960.h>
const int buttonPin = 2;
const int speakerPin = 4;
int pushupState = -1;
int buttonState = 0;
const int startThreshold = 230; // <--- the lowest threshold distance from a person's chest to the floor
const int endThreshold = 235; // <--- the highest threshold distance from a person's chest to the floor

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  pinMode(buttonPin, INPUT);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // check if a proximity reading is available
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    pushupState = 0;
    Serial.println("New:");
  }

  if (APDS.proximityAvailable() && pushupState != -1) {
    int proximity = APDS.readProximity();

    if (proximity > endThreshold) {
      if (pushupState == 3) {
        digitalWrite(speakerPin, HIGH);  // turn the speaker on
        delay(100);
        digitalWrite(speakerPin, LOW);
      }

      pushupState = 0;
    } else if (proximity < startThreshold) {
      pushupState = 2;
    } else {
      if (pushupState == 0) {
        pushupState = 1;
      } else if (pushupState == 2) {
        pushupState = 3;
      }
    }
  }

  // wait a bit before reading again
  delay(100);
}
