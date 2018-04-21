#define PROG2_MAX_STEP 16
const int PROG2_H = 450;

boolean prog2On = false;
byte prog2Step = 0;
float prog2ACos = 0;
float prog2ASin = 0;
int prog2H = 0;
int prog2L = 0;

int prog2LaserH[2] = {0, 0};
int prog2LI = 0;

void prog2Loop() {
  if (prog2On == false) {
    return;
  }
  Serial.print(" prog2 s=");
  Serial.print(prog2Step);
  Serial.print(" ");
  if (prog2Step == 0) {
    armSetA(90);
    int prog2A = (millis() % 140) + 20;
    prog2ACos = cos(prog2A * 0.017453);
    prog2ASin = sin(prog2A * 0.017453);
    prog2Step = 1;
    prog2L = ARM_L;
    prog2H = PROG2_H;
    prog2LI = 200;
    armSetXYZ(0, prog2LI, PROG2_H);
  } else if (prog2Step == 1 && servoDone()) {
    prog2LaserH[1] = laserVal();
    if (prog2LaserH[1] - prog2LaserH[0] > 70) {
      prog2L = prog2LI + 50;
    }
    prog2LaserH[0] = prog2LaserH[1];
    armSetXYZ(prog2LI * prog2ACos, prog2LI * prog2ASin, prog2H);
    prog2LI += 50;
    if (prog2LI >= ARM_L) {
       prog2Step = 2;
    }
  } else if (prog2Step == 2 && servoDone()) {
    armSetA(80);
    prog2Step = 3;
  } else if (prog2Step == 3 && servoDone()) {
    int x = touchX();
    if (x > 32 && x < 128) {
      prog2L -= 10;
    }
    if (x >= 128) {
      prog2H++;
    }
    if (x < 32) {
      prog2H--;
    }
    if (prog2H > PROG2_H) {
      prog2H = PROG2_H;
    }
    if (prog2H < 100) {
      prog2H = 100;
      prog2L -= 10;
    }
    if (prog2L < 100) {
      prog2Step = 0;
    }
    armSetXYZ(prog2L * prog2ACos, prog2L * prog2ASin, prog2H);
  }
}

void prog2Stop() {
  prog2On = false;
  prog2Step = 0;
}

void prog2Start() {
  prog2On = true;
  prog2Step = 0;
}
