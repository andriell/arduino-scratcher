#include <Servo.h>

unsigned long timeUpdate;

void setup() {
  servoSetup();
}

void loop() {
  delay(50);
  servoLoop();
  unsigned long time = micros();
  if (time > timeUpdate) {
    s0Set(random(0, 180));
    s1Set(random(0, 180));
    s2Set(random(0, 180));
    s3Set(random(0, 180));
    timeUpdate = time + 30000000;
  }
}

