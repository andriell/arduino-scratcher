#define ARM_PI 3.1416
const long ARM_A1 = 450;
const long ARM_A2 = 370;
const long ARM_L  = 820;

int armA = 0;

boolean armSetXYZ(long x, long y, long z) {
  boolean r = true;
  long l = sqrt(x * x + y * y + z * z);
  if (l > ARM_A1 + ARM_A2 - 50) {
    l = ARM_A1 + ARM_A2 - 50;
    r = false;
  }
  long l1 = (l * l + ARM_A1 * ARM_A1 - ARM_A2 * ARM_A2) / (2 * l);
  long l2 = l - l1;
  long h = sqrt(ARM_A1 * ARM_A1 - l1 * l1);
  long xy = sqrt(x * x + y * y);
  int a0 = round(atan2(y,  x) * 180 / ARM_PI);
  int a1 = round(atan2(h, l1) * 180 / ARM_PI);
  int a2 = round(atan2(h, l2) * 180 / ARM_PI);
  int a3 = round(atan2(z, xy) * 180 / ARM_PI);
  r = servoSet(0, a0) && r;
  r = servoSet(1, 180 - a1 - a3) && r;
  r = servoSet(2, 180 - a1 - a2) && r;
  r = servoSet(3, a3 - a2 + armA) && r;
  Serial.print(" arm x=");
  Serial.print(x);
  Serial.print(" y=");
  Serial.print(y);
  Serial.print(" z=");
  Serial.print(z);
  Serial.print(" l=");
  Serial.print(l);
  Serial.print(" l1=");
  Serial.print(l1);
  Serial.print(" l2=");
  Serial.print(l2);
  Serial.print(" h=");
  Serial.print(h);
  Serial.print(" a0=");
  Serial.print(a0);
  Serial.print(" a1=");
  Serial.print(a1);
  Serial.print(" a2=");
  Serial.print(a2);
  Serial.print(" a3=");
  Serial.print(a3);
  Serial.print(" r=");
  Serial.print (r);
  return r;
}

void armSetA(int a) {
  armA = a;
}


