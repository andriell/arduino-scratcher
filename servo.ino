struct ServoStruct {
  int need;
  int current;
  int normal;
  int vMin;
  int vMax;
  unsigned long speed;
  unsigned long time;
  boolean available;
  Servo servo;
};

#define S0_PIN 7
#define S1_PIN 6
#define S2_PIN 5
#define S3_PIN 4

ServoStruct servos[4] = {
  {90, 90, 90, 0, 180, 20000, 0, false},
  { 0,  0,  0, 0, 180, 20000, 0, false},
  { 0,  0,  0, 0, 180, 20000, 0, false},
  { 0,  0,  0, 0, 180, 20000, 0, false}
};

/**
 * 1 - включено
 * 2 - начало выключения
 * 3 - выключение
 * 4 - выключение
 * 5 - выключено
 */
byte servoStage = 1;
bool servoIsDone = true;

void servoSetup() {
  servos[0].servo.attach(S0_PIN);
  servos[1].servo.attach(S1_PIN);
  servos[2].servo.attach(S2_PIN);
  servos[3].servo.attach(S3_PIN);
  for (int i = 0; i < 4; i++) {
    servos[i].servo.write(servos[i].normal);
  }
}

void servoLoop() {
  if (servoStage == 1 || servoStage == 2 || servoStage == 3 || servoStage == 4) {
    servoIsDone = true;
    unsigned long time = micros();
    Serial.print(" servo ");
    for (int i = 0; i < 4; i++) {
      Serial.print(i);
      Serial.print(":");
      Serial.print(servos[i].current);
      Serial.print(">");
      Serial.print(servos[i].need);
      Serial.print(" | ");
      if (servos[i].available == false) {
        continue;
      }
      if (servos[i].need == servos[i].current) {
        continue;
      } else {
        servoIsDone = false;
      }
      if (servos[i].speed + servos[i].time > time) {
        continue;
      }
      servos[i].time = time;
      if (servos[i].need > servos[i].current) {
        servos[i].current++;
      } else {
        servos[i].current--;
      }
      servos[i].servo.write(servos[i].current);
    }
  }
  if (servoStage == 2) {
    servos[1].need = 90;
    servos[1].available = true;
    servoIsDone = false;
    servoStage = 3;
  } else if (servoStage == 3 && servoIsDone) {
    for (int i = 0; i < 4; i++) {
      servos[i].available = true;
      servos[i].need == servos[i].normal;
    }
    servoStage = 4;
  } else if (servoStage == 4 && servoIsDone) {
    servoStage = 5;
    beep();
  }
}

boolean servoSet(int i, int a) {
  if (servoStage != 1) {
    return false;
  }
  boolean r = true;
  if (a < servos[i].vMin) {
    a = servos[i].vMin;
    r = false;
  }
  if (a > servos[i].vMax) {
    a = servos[i].vMax;
    r = false;
  }
  servoIsDone = servos[i].need == a;
  servos[i].need = a;
  return r;
}

boolean servoDone() {
  return servoIsDone;
}

void servoOn() {
  servos[0].available = true;
  servos[1].available = true;
  servos[2].available = true;
  servos[3].available = true;
  servoStage = 1;
}

void servoOff() {
  servos[0].available = false;
  servos[1].available = false;
  servos[2].available = false;
  servos[3].available = false;
  servoStage = 2;
}

