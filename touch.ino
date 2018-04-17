const int TOUCH_X_PIN = A0;
const int TOUCH_Y_PIN = A1;

int touchXVal = 0;
int touchYVal = 0;

boolean touchTest = false;
long touchTestXYZ[3] = {500, 500, 500};

void touchSetup() {
  pinMode(TOUCH_X_PIN, INPUT);
  pinMode(TOUCH_X_PIN, INPUT);
}

void touchLoop() {
  touchXVal = analogRead(TOUCH_X_PIN) - 512;
  touchYVal = analogRead(TOUCH_Y_PIN) - 512;
  Serial.print(" toch x=");
  Serial.print(touchXVal);
  Serial.print(" y=");
  Serial.print(touchYVal);
  //if (touchTest) {
    if (touchXVal < -50) {
      touchTestXYZ[2]++;
    }
    if (touchXVal > 50) {
      touchTestXYZ[2]--;
    }
    if (touchYVal < -50) {
      touchTestXYZ[0]++;
    }
    if (touchYVal > 50) {
      touchTestXYZ[0]--;
    }
    armSetXYZ(touchTestXYZ[0], touchTestXYZ[1], touchTestXYZ[2]);
  //}
}

void touchTestStart() {
  touchTest = true;
  touchTestXYZ[0] = 0;
  touchTestXYZ[1] = 500;
  touchTestXYZ[2] = 500;
}

int touchX() {
  return touchXVal;
}

int touchY() {
  return touchYVal;
}

