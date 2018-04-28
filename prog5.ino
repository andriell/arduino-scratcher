#define PROG5_MAX_STEP 16
const int PROG5_H = 300; // Высота перемещения
const int PROG5_D = 400; // Расстояние до тела

boolean prog5On = false;
byte prog5Step = 0;
float prog5ACos = 0;
float prog5ASin = 0;
int prog5L = 0;
int prog5HMap[20] = {
  100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
  100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};
int prog5HMapI = 10;
int prog5XMax = 128;

void prog5Loop() {
  if (prog5On == false) {
    return;
  }
  Serial.print(" prog5 s=");
  Serial.print(prog5Step);
  Serial.print(" prog5L=");
  Serial.print(prog5L);
  Serial.print(" ");
  if (prog5Step == 0) { // Начальное положение
    armSetA(90);
    int prog5A = (millis() % 140) + 20;
    prog5ACos = cos(prog5A * 0.017453);
    prog5ASin = sin(prog5A * 0.017453);
    armSetXYZ(0, 200, PROG5_H);
    prog5Step = 1;
    if (prog5ASin == 0) {
      prog5L = ARM_L;
    } else {
      prog5L = abs(PROG5_D / prog5ASin);
    }
    if (prog5L > ARM_L) {
      prog5L = ARM_L;
    }
    prog5HMapI = round(float(prog5L * prog5ACos) / 5.0f) + 10;
    prog5HMapI = constrain(prog5HMapI, 0, 19);
    prog5XMax = 0;
  } else if (prog5Step == 1 && servoDone()) { // Перемещение к дальней точке
    armSetXYZ(prog5L * prog5ACos, prog5L * prog5ASin, PROG5_H);
    prog5Step = 2;
  } else if (prog5Step == 2 && servoDone()) { // Наклон кисти
    armSetA(110);
    prog5Step = 3;
  } else if (prog5Step == 3 && servoDone()) { // Чес
    prog5XMax = max(prog5XMax, touchX());
    prog5L -= 5;
    if (prog5L < 100) {
      prog5Step = 4;
    }
    armSetXYZ(prog5L * prog5ACos, prog5L * prog5ASin, prog5HMap[prog5HMapI]);
  } else if (prog5Step == 4) { // Калибровка
    if (prog5XMax > 448) {
      prog5HMap[prog5HMapI] += 20;
    }
    if (prog5XMax < 256) {
      prog5HMap[prog5HMapI] -= 20;
    }
    prog5Step = 0;
  }
}

void prog5Stop() {
  prog5On = false;
  prog5Step = 0;
}

void prog5Start() {
  prog5On = true;
  prog5Step = 0;
}
