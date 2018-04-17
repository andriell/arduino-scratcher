#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

unsigned long timeUpdate;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  laserSetup();
  servoSetup();
}
int andle = 180;
void loop() {
  delay(50);
  laserLoop();
  servoLoop();
  unsigned long time = micros();
  if (time > timeUpdate) {
    servoSet(0, andle);
    servoSet(1, andle);
    servoSet(2, andle);
    if (andle == 0) {
      andle = 180;
    } else {
      andle = 0;
    }
    timeUpdate = time + 30000000;
  }
}

