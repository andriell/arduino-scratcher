#define PROG1_MAX_STEP 16
const int PROG1_H = 450;

struct prog1Struct {
  int x;
  int y;
  unsigned int h;
};

prog1Struct prog1Point[PROG1_MAX_STEP] = {
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},
};
boolean prog1On = false;
byte prog1Step = 0;
byte prog1I = 0;
float prog1ACos = 0;
float prog1ASin = 0;

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
    Serial.print(" A=");
    Serial.print(prog1A);
    for (int i = 0; i < PROG1_MAX_STEP; i++) {
      prog1Point[i].x = (50 * i + 200) * prog1ACos;
      prog1Point[i].y = (50 * i + 200) * prog1ASin;
      Serial.print(" ");
      Serial.print(prog1Point[i].x);
      Serial.print("x");
      Serial.print(prog1Point[i].y);
      Serial.print(" ");
    }
    armSetXYZ(0, 200, PROG1_H);
    prog1Step = 1;
    prog1I = 0;
  } else if (prog1Step == 1 && servoDone()) {
    prog1Point[prog1I].h = laserVal();
    prog1I++;
    if (prog1I >= PROG1_MAX_STEP) {
       prog1Step = 2;
       prog1I = PROG1_MAX_STEP - 1;
    } else {
      armSetXYZ(prog1Point[prog1I].x, prog1Point[prog1I].y, PROG1_H);
    }
  } else if (prog1Step == 2) {
    int minH = 2000;
    int maxH = 0;
    for (int i = 0; i < PROG1_MAX_STEP; i++) {
      minH = min(minH, prog1Point[i].h);
      maxH = max(maxH, prog1Point[i].h);
    }
    for (int i = 0; i < PROG1_MAX_STEP; i++) {
      if ((prog1Point[i].h - (minH + maxH) / 2) < 70) {
        prog1Point[i].h = 0;
      }
      Serial.print(" ");
      Serial.print(prog1Point[i].h);
    }
    armSetA(45);
    prog1Step = 3;
    prog1I = PROG1_MAX_STEP - 1;
  } else if (prog1Step == 3) {
    while(prog1Point[prog1I].h <= 0 && prog1I >= 0) {
      prog1I--;
    }
    Serial.print(" i=");
    Serial.print(prog1I);
    if (prog1I <= 0) {
      prog1Step = 0;
    } else {
      armSetXYZ(prog1Point[prog1I].x - 50 * prog1ACos, prog1Point[prog1I].y - 50 * prog1ASin, PROG1_H - prog1Point[prog1I].h + 50);
    }
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
