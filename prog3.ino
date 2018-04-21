#define PROG3_MAX_STEP 16
const int PROG3_H = 450;
const int PROG3_HS = 200;
const int PROG3_D = 400;

boolean prog3On = false;
byte prog3Step = 0;
float prog3ACos = 0;
float prog3ASin = 0;
int prog3H = 0;
int prog3L = 0;

void prog3Loop() {
  if (prog3On == false) {
    return;
  }
  Serial.print(" prog3 s=");
  Serial.print(prog3Step);
  Serial.print(" ");
  if (prog3Step == 0) {
    armSetA(90);
    int prog3A = (millis() % 140) + 20;
    prog3ACos = cos(prog3A * 0.017453);
    prog3ASin = sin(prog3A * 0.017453);
    armSetXYZ(0, 200, PROG3_H);
    prog3Step = 1;
    prog3L = PROG3_D / prog3ACos;
    if (prog3L > ARM_L) {
      prog3L = ARM_L;
    }
    prog3H = PROG3_HS;
  } else if (prog3Step == 1 && servoDone()) {
    armSetXYZ(prog3L * prog3ACos, prog3L * prog3ASin, prog3H);
    prog3Step = 2;
  } else if (prog3Step == 2 && servoDone()) {
    armSetA(80);
    prog3Step = 3;
  } else if (prog3Step == 3 && servoDone()) {
    int x = touchX();
    if (x > 32 && x < 128) {
      prog3L -= 10;
    }
    if (x >= 128) {
      prog3H++;
    }
    if (x < 32) {
      prog3H--;
    }
    if (prog3H > PROG3_H) {
      prog3H = PROG3_H;
    }
    if (prog3H < 100) {
      prog3H = 100;
      prog3L -= 10;
    }
    if (prog3L < 100) {
      prog3Step = 0;
    }
    armSetXYZ(prog3L * prog3ACos, prog3L * prog3ASin, prog3H);
  }
}

void prog3Stop() {
  prog3On = false;
  prog3Step = 0;
}

void prog3Start() {
  prog3On = true;
  prog3Step = 0;
}
