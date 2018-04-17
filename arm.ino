#define ARM_PI 3.1416
const long ARM_A1 = 500;
const long ARM_A2 = 450;

long armXYZ[3] = {0, 0, 0};
int armA = 0;

void armSetA(int a) {
  armA = a;
}

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
  int a0 = round(atan2(y, x) * 180 / ARM_PI + 90);
  int a1 = round(atan2(h, l1) * 180 / ARM_PI);
  int a2 = round(atan2(h, l2) * 180 / ARM_PI);
  int a3 = round(atan2(z, sqrt(x * x + y * y)) * 180 / ARM_PI);
  r = r && sSet(0, a0);
  r = r && sSet(1, a1);
  r = r && sSet(2, a2);
  r = r && sSet(2, a3 + armA);
  return r;
}

