#include "hsv_to_rgb.h"
#include <cmath>
#include <algorithm>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html#:~:text=Converting%20HSV%20to%20RGB&text=For%20example%2C%20if%20H%20%3D%20135,you%20divide%20it%20by%202.&text=B%20%3D%20m.&text=B%20%3D%20m.,-If%20120%20%E2%89%A4
  */
    double M = 255.0 * v;
    double m = M * (1 - s);
    double z = (M - m)*(1 - std::fabs(std::fmod((h / 60), 2) - 1));
    if (h >= 0 && h < 60) {
        r = M;
        g = z + m;
        b = m;
    }
    else if (h >= 60 && h < 120) {
        r = z + m;
        g = M;
        b = m;
    }
    else if (h >= 120 && h < 180) {
        r = m;
        g = M;
        b = z + m;
    }
    else if (h >= 180 && h < 240) {
        r = m;
        g = z + m;
        b = M;
    }
    else if (h >= 240 && h < 300) {
        r = z + m;
        g = m;
        b = M;
    }
    else if (h >= 300 && h < 360) {
        r = M;
        g = m;
        b = z + m;
    }
  ////////////////////////////////////////////////////////////////////////////
}
