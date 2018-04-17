VL53L0X laserSensor;

unsigned int laserValue = 0;

boolean laserTest = false;
long laserTestXYZ[3] = {500, 500, 500};

void laserSetup() {
  laserSensor.init();
  laserSensor.setTimeout(500);
  // Высокая точность
  // increase timing budget to 200 ms
  laserSensor.setMeasurementTimingBudget(200000);
}

void laserLoop() {
  laserValue = laserSensor.readRangeSingleMillimeters();
  Serial.print(" laser ");
  Serial.print(laserValue);
  if (laserTest) {
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

unsigned int laserVal() {
  return laserValue;
}

