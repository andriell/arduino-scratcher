#include <Servo.h>

unsigned long timeUpdate;

void setup() {
  servoSetup();
}
int andle = 0;
void loop() {
  delay(50);
  servoLoop();
  unsigned long time = micros();
  if (time > timeUpdate) {
    s0Set(andle);
    s1Set(andle);
    s2Set(andle);
    s3Set(andle);
    if (andle == 0) {
      andle = 180;
    } else {
      andle = 0;
    }
    timeUpdate = time + 30000000;
  }
}

