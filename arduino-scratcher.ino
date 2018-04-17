#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

boolean inited = false;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  laserSetup();
  servoSetup();
}

void loop() {
  delay(50);
  armSetXYZ(500, 500, 500);
  touchLoop();
  laserLoop();
  servoLoop();
  Serial.println();
}

