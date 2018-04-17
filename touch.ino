const int TOUCH_X_PIN = A1;
const int TOUCH_Y_PIN = A0;

int touchXVal = 0;
int touchYVal = 0;

void touchSetup() {
  pinMode(TOUCH_X_PIN, INPUT);
  pinMode(TOUCH_X_PIN, INPUT);
}

void touchLoop() {
  touchXVal = analogRead(TOUCH_X_PIN) - 512;
  touchYVal = analogRead(TOUCH_Y_PIN) - 512;
}

int touchX() {
  return touchXVal;
}

int touchY() {
  return touchYVal;
}

