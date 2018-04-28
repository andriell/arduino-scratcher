const int CONTROL_PIN = 11;

IRrecv controlIR(CONTROL_PIN);
decode_results controlResults;

// 0 - 9 - цифры
// 10 - вверх
// 11 - вправо
// 12 - вниз
// 13 - влево
// 14 - Ok
// 15 - *
// 16 - #
byte control = 0;

void controlSetup() {
  controlIR.enableIRIn();
}

void controlLoop() {
  control = 0;
  Serial.print(" controll ");
  if (controlIR.decode(&controlResults)) {
    bitSet(control, 20);
    Serial.print(controlResults.value);
    switch (controlResults.value) {
      case 16753245:
        control = 1;
        break;
      case 16736925:
        control = 2;
        break;
      case 16769565:
        control = 3;
        break;
      case 16720605:
        control = 4;
        break;
      case 16712445:
        control = 5;
        break;
      case 16761405:
        control = 6;
        break;
      case 16769055:
        control = 7;
        break;
      case 16754775:
        control = 8;
        break;
      case 16748655:
        control = 9;
        break;
      case 16738455:
        control = 15;
        break;
      case 16750695:
        control = 0;
        break;
      case 16756815:
        control = 16;
        break;
      case 16718055:
        control = 10;
        break;
      case 16716015:
        control = 13;
        break;
      case 16726215:
        control = 14;
        break;
      case 16734885:
        control = 11;
        break;
      case 16730805:
        control = 12;
        break;
    };
    controlIR.resume();
  }
  Serial.print("-");
  Serial.print(control);
  if (control == 1) {
    controlStopAll();
    prog1Start();
  } else if (control == 2) {
    controlStopAll();
    prog2Start();
  } else if (control == 3) {
    controlStopAll();
    prog3Start();
  } else if (control == 4) {
    controlStopAll();
    prog4Start();
  } else if (control == 5) {
    controlStopAll();
    prog5Start();
  } else if (control == 8) {
    controlStopAll();
    laserTestStart();
  } else if (control == 9) {
    controlStopAll();
    touchTestStart();
  } else if (control == 15) {
    servoOff();
  } else if (control == 16) {
    servoOn();
  }
}

void controlStopAll() {
  touchTestStop();
  laserTestStop();
  prog1Stop();
  prog2Stop();
  prog3Stop();
  prog4Stop();
  prog5Stop();
}

boolean controlRead(int i) {
  return bitRead(control, i);
}

