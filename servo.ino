struct ServoStruct {
  int need;
  int current;
  int normal;
  unsigned long speed;
  unsigned long time;
  Servo servo;
};

#define S0_PIN 7
#define S1_PIN 6
#define S2_PIN 5
#define S3_PIN 4

ServoStruct servos[4] = {
  {90, 90, 90, 50000, 0},
  {0, 0, 0, 50000, 0},
  {0, 0, 0, 50000, 0},
  {0, 0, 0, 50000, 0}
};

void servoSetup() {
  servos[0].servo.attach(S0_PIN);
  servos[1].servo.attach(S1_PIN);
  servos[2].servo.attach(S2_PIN);
  servos[3].servo.attach(S3_PIN);
}

void servoLoop() {
  unsigned long time = micros();
  for (int i = 0; i < 4; i++) {
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

void s0Set(int a) {
  servos[0].need = a;
}

void s1Set(int a) {
  servos[1].need = a;
}

void s2Set(int a) {
  servos[2].need = a;
}

void s3Set(int a) {
  servos[3].need = a;
}
