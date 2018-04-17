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
  {90, 90, 90, 0, 180, 20000, 0},
  {0, 0, 0, 0, 180, 20000, 0},
  {0, 0, 0, 0, 180, 20000, 0},
  {0, 0, 0, 0, 180, 20000, 0}
};

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
  for (int i = 0; i < 3; i++) {
    Serial.print(i);
    Serial.print(" ");
    Serial.print(servos[i].current);
    Serial.print(" ");
    Serial.println(servos[i].need);
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
}

boolean sSet(int i, int a) {
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
