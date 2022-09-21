#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {

          int idx = 3 * (col + row * width);
          double h = 0.0, s = 0.0, v = 0.0;
          double r = rgb[idx + 0];
          double g = rgb[idx + 1];
          double b = rgb[idx + 2];

          rgb_to_hsv(r, g, b, h, s, v);

          // shift the hue, then make sure new h is between 0 and 360 degrees
          h -= shift;
          if (h > 360.0) {
              h = std::fmod(h, 360.0);
          }
          else if (h < 0.0)
          {
              h = 360.0 - std::fmod(std::abs(h), 360.0);
          }

          hsv_to_rgb(h, s, v, r, g, b);

          shifted[idx + 0] = (unsigned char) r;
          shifted[idx + 1] = (unsigned char) g;
          shifted[idx + 2] = (unsigned char) b;
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
