#define PROG1_MAX_STEP 16
const int PROG1_H = 450;

boolean prog1On = false;
byte prog1Step = 0;
float prog1ACos = 0;
float prog1ASin = 0;
int prog1H = 0;
int prog1L = 0;

void prog1Loop() {
  if (prog1On == false) {
    return;
  }
  Serial.print(" prog1 s=");
  Serial.print(prog1Step);
  Serial.print(" ");
  if (prog1Step == 0) {
    armSetA(90);
    int prog1A = (millis() % 140) + 20;
    prog1ACos = cos(prog1A * 0.017453);
    prog1ASin = sin(prog1A * 0.017453);
    armSetXYZ(0, 200, PROG1_H);
    prog1Step = 1;
    prog1L = ARM_L;
    prog1H = PROG1_H;
  } else if (prog1Step == 1 && servoDone()) {
    armSetXYZ(prog1L * prog1ACos, prog1L * prog1ASin, prog1H);
    prog1Step = 2;
  } else if (prog1Step == 2 && servoDone()) {
    armSetA(80);
    prog1Step = 3;
  } else if (prog1Step == 3 && servoDone()) {
    int x = touchX();
    if (x > 32 && x < 128) {
      prog1L -= 10;
    }
    if (x >= 128) {
      prog1H++;
    }
    if (x < 32) {
      prog1H--;
    }
    if (prog1H > PROG1_H) {
      prog1H = PROG1_H;
    }
    if (prog1H < 100) {
      prog1H = 100;
      prog1L -= 10;
    }
    if (prog1L < 100) {
      prog1Step = 0;
    }
    armSetXYZ(prog1L * prog1ACos, prog1L * prog1ASin, prog1H);
  }
}

void prog1Stop() {
  prog1On = false;
  prog1Step = 0;
}

void prog1Start() {
  prog1On = true;
  prog1Step = 0;
}
