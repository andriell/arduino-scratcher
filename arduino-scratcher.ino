#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <IRremote.h>

boolean inited = false;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  laserSetup();
  servoSetup();
  touchTestStart();
  //laserTestStart();
}

void loop() {
  //delay(50);
  touchLoop();
  //laserLoop();
  servoLoop();
  Serial.println(micros());
}

