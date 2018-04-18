VL53L0X laserSensor;

boolean laserTest = false;
long laserTestXYZ[3] = {0, 0, 0};

void laserSetup() {
  laserSensor.init();
  laserSensor.setTimeout(500);
  // Высокая точность
  // increase timing budget to 200 ms
  laserSensor.setMeasurementTimingBudget(200000);
}

void laserLoop() {
  if (laserTest) {
    unsigned int laserValue = laserVal();
    if (laserValue > 500) {
      laserTestXYZ[1]++;
    }
    if (laserValue < 400) {
      laserTestXYZ[1]--;
    }
    armSetXYZ(laserTestXYZ[0], laserTestXYZ[1], laserTestXYZ[2]);
  }
}

void laserTestStart() {
  laserTest = true;
  laserTestXYZ[0] = 0;
  laserTestXYZ[1] = 50;
  laserTestXYZ[2] = 500;
  armSetA(0);
}

void laserTestStop() {
  laserTest = false;
}

unsigned int laserVal() {
  unsigned int laserValue = laserSensor.readRangeSingleMillimeters();
  Serial.print(" laser ");
  Serial.print(laserValue);
  return laserValue;
}

