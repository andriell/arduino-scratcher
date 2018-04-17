struct ServoStruct {
  int need;
  int current;
  int normal;
  int vMin;
  int vMax;
  unsigned long speed;
  unsigned long time;
  Servo servo;
};

#define S0_PIN 7
#define S1_PIN 6
#define S2_PIN 5
#define S3_PIN 4


ServoStruct servos[4] = {
  {90, 90, 90, 0, 180, 200, 0},
  { 0,  0,  0, 0, 180, 200, 0},
  { 0,  0,  0, 0, 180, 200, 0},
  { 0,  0,  0, 0, 180, 200, 0}
};

boolean servoOn = true;

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
  unsigned long time = micros();
  Serial.print(" servo ");
  for (int i = 0; i < 4; i++) {
    Serial.print(i);
    Serial.print(":");
    Serial.print(servos[i].current);
    Serial.print(">");
    Serial.print(servos[i].need);
    Serial.print(" | ");
    if (servos[i].need == servos[i].current) {
      continue;
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
  if (!servoOn) {
    boolean r = true;
    for (int i = 1; i < 4; i++) {
      servos[i].need = servos[i].normal;
      r = r && servos[i].need == servos[i].current;
    }
    if (r) {
      servos[0].need = servos[0].normal;
    }
    if (abs(servos[0].need - servos[0].normal) == 1) {
      beep();
    }
  }
}

boolean servoSet(int i, int a) {
  if (!servoOn) {
    return false;
  }
  if (a < servos[i].vMin) {
    servos[i].need = servos[i].vMin;
    return false;
  }
  if (a > servos[i].vMax) {
    servos[i].need = servos[i].vMax;
    return false;
  }
  servos[i].need = a;
  return true;
}

boolean servoDone() {
  boolean r = true;
  for (int i = 0; i < 4; i++) {
    r = r && servos[i].need == servos[i].current;
  }
  return r;
}

boolean servoOff() {
  servoOn = false;
}

