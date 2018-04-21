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
  {90, 90, 90, 0, 180, 40000, 0, false},
  { 0,  0,  0, 0, 180, 40000, 0, false},
  { 0,  0,  0, 0, 180, 20000, 0, false},
  { 0,  0,  0, 0, 180, 10000, 0, false}
};

/**
 * 1 - включено
 * 2 - начало выключения
 * 3 - выключение
 * 4 - выключено
 */
byte servoStage = 4;
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
  Serial.print(" servo");
  Serial.print(servoStage);
  Serial.print(" ");
  if (servoStage == 1 || servoStage == 2 || servoStage == 3) {
    servoIsDone = true;
    unsigned long time = micros();
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
    if (servos[1].current == 90) {
      for (int i = 0; i < 4; i++) {
        servos[i].available = true;
        servos[i].need = servos[i].normal;
      }
      servoStage = 3;
    }
  } else if (servoStage == 3 && servoIsDone) {
    servoStage = 4;
    beep();
  }
}

boolean servoSet(int i, int a) {
  Serial.print(" ss");
  Serial.print(i);
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
  Serial.print("=");
  Serial.print(a);
  Serial.print(":");
  Serial.print(r);
  return r;
}

boolean servoDone() {
  return servoIsDone;
}

void servoOn() {
  if (servoStage != 4) {
    return;
  }
  servos[0].available = true;
  servos[1].available = true;
  servos[2].available = true;
  servos[3].available = true;
  servoStage = 1;
}

void servoOff() {
  if (servoStage != 1) {
    return;
  }
  servos[0].available = false;
  servos[1].available = true;
  servos[2].available = false;
  servos[3].available = false;
  servos[1].need = 90;
  servoStage = 2;
}

