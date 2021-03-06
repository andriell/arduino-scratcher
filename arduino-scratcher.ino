#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <IRremote.h>

boolean inited = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  laserSetup();
  servoSetup();
  controlSetup();
  //touchTestStart();
  //laserTestStart();
}

void loop() {
  touchLoop();
  laserLoop();
  servoLoop();
  controlLoop();
  prog1Loop();
  prog2Loop();
  prog3Loop();
  prog4Loop();
  prog5Loop();
  Serial.print(" m ");
  Serial.println(micros());
}

