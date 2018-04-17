#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

boolean inited = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  laserSetup();
  servoSetup();
}

void initialization() {
  touchTestStart();
}

void loop() {
  delay(50);
  if (!inited) {
    initialization();
    inited = true;
  }
  touchLoop();
  laserLoop();
  servoLoop();
  Serial.println();
}

