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
unsigned long control = 0;

void controlSetup() {
  controlIR.enableIRIn();
}

void controlLoop() {
  if (controlIR.decode(&controlResults)) {
    switch (controlResults.value) {
      case 0xFFA25D:
        bitSet(control, 1);
        break;
      case 0xFF629D:
        bitSet(control, 2);
        break;
      case 0xFFE21D:
        bitSet(control, 3);
        break;
      case 0xFF22DD:
        bitSet(control, 4);
        break;
      case 0xFF02FD:
        bitSet(control, 5);
        break;
      case 0xFFC23D:
        bitSet(control, 6);
        break;
      case 0xFFE01F:
        bitSet(control, 7);
        break;
      case 0xFFA857:
        bitSet(control, 8);
        break;
      case 0xFF906F:
        bitSet(control, 9);
        break;
      case 0xFF6897:
        bitSet(control, 15);
        break;
      case 0xFF9867:
        bitSet(control, 0);
        break;
      case 0xFFB04F:
        bitSet(control, 16);
        break;
      case 0xFF18E7:
        bitSet(control, 10);
        break;
      case 0xFF10EF:
        bitSet(control, 13);
        break;
      case 0xFF38C7:
        bitSet(control, 14);
        break;
      case 0xFF5AA5:
        bitSet(control, 11);
        break;
      case 0xFF4AB5:
        bitSet(control, 12);
        break;
    };
  }
}

