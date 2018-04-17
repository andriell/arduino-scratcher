VL53L0X laserSensor;

unsigned int laserValue = 0;

void laserSetup() {
  laserSensor.init();
  laserSensor.setTimeout(500);
  // Высокая точность
  // increase timing budget to 200 ms
  laserSensor.setMeasurementTimingBudget(200000);
}

void laserLoop() {
  laserValue = laserSensor.readRangeSingleMillimeters();
}

unsigned int laserVal() {
  return laserValue;
}

