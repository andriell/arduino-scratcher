#define PROG4_MAX_STEP 16
const int PROG4_H = 450;
const int PROG4_HS = 100;
const int PROG4_D = 400;

boolean prog4On = false;
byte prog4Step = 0;
float prog4ACos = 0;
float prog4ASin = 0;
int prog4L = 0;

void prog4Loop() {
  if (prog4On == false) {
    return;
  }
  Serial.print(" prog4 s=");
  Serial.print(prog4Step);
  Serial.print(" prog4L=");
  Serial.print(prog4L);
  Serial.print(" ");
  if (prog4Step == 0) {
    armSetA(90);
    int prog4A = (millis() % 140) + 20;
    prog4ACos = cos(prog4A * 0.017453);
    prog4ASin = sin(prog4A * 0.017453);
    armSetXYZ(0, 200, PROG4_H);
    prog4Step = 1;
    if (prog4ASin == 0) {
      prog4L = ARM_L;
    } else {
      prog4L = abs(PROG4_D / prog4ASin);
    }
    if (prog4L > ARM_L) {
      prog4L = ARM_L;
    }
  } else if (prog4Step == 1 && servoDone()) {
    armSetXYZ(prog4L * prog4ACos, prog4L * prog4ASin, PROG4_H);
    prog4Step = 2;
  } else if (prog4Step == 2 && servoDone()) {
    armSetA(100);
    prog4Step = 3;
  } else if (prog4Step == 3 && servoDone()) {
    prog4L -= 5;
    if (prog4L < 100) {
      prog4Step = 0;
    }
    armSetXYZ(prog4L * prog4ACos, prog4L * prog4ASin, PROG4_HS);
  }
}

void prog4Stop() {
  prog4On = false;
  prog4Step = 0;
}

void prog4Start() {
  prog4On = true;
  prog4Step = 0;
}
