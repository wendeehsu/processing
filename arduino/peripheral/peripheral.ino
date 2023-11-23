#include <ArduinoBLE.h>

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const int speakerPin = 4;
const int buttonPin = 2;

bool startCounting = false;
int payment = 5;
int paidValue = -1;

BLEService peripheralService(deviceServiceUuid);
BLEByteCharacteristic firstCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(speakerPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
    ;

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(peripheralService);
  peripheralService.addCharacteristic(firstCharacteristic);
  BLE.addService(peripheralService);
  firstCharacteristic.writeValue(-1);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}

void loop() {
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      int buttonState = digitalRead(buttonPin);
      if (buttonState == LOW) {
        startCounting = true;
        paidValue = -1;
      }

      if (firstCharacteristic.written() && startCounting) {
        int val = firstCharacteristic.value();
        if (paidValue == -1) {
          paidValue = val;
          Serial.print("start with val:");
        } else if (val - paidValue == payment - 1) {
          // show result here
          startCounting = false;
          paidValue = -1;
          Serial.print("eeeeeeeeeeend with val:");
        }
        Serial.println(val);
        digitalWrite(speakerPin, HIGH);  // turn the speaker on
        delay(100);
        digitalWrite(speakerPin, LOW);
      }
    }

    Serial.println("* Disconnected to central device!");
  }
}