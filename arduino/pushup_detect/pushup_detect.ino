#include <Arduino_APDS9960.h>
const int buttonPin = 2;
bool hasStarted = false;
int buttonState = 0;
bool hasPush = false;
const int threshold = 230; // <--- the threshold distance from a person's chest to the floor

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  pinMode(buttonPin, INPUT);
}

void loop() {
  // check if a proximity reading is available
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    hasStarted = true;
    Serial.println("New:");
  }

  if (APDS.proximityAvailable() && hasStarted) {
    int proximity = APDS.readProximity();

    if (!hasPush && proximity < threshold) {
      Serial.print("======== 1 push start -->");
      Serial.print(proximity);
      hasPush = true;
    }
    else if (hasPush && proximity > threshold) {
      Serial.print("-->");
      Serial.print(proximity);
      Serial.println("--> 1 push end ========");
      hasPush = false;
    }
  }

  // wait a bit before reading again
  delay(100);
}
