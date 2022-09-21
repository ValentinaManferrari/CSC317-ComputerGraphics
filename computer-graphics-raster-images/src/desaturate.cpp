#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {

          int idx = 3 * (col + row * width);
          double h = 0.0, s = 0.0, v = 0.0;

          double r = rgb[idx + 0];
          double g = rgb[idx + 1];
          double b = rgb[idx + 2];

          rgb_to_hsv(r, g, b, h, s, v);

          //change saturation by a given factor
          s *= (1 - factor);

          hsv_to_rgb(h, s, v, r, g, b);

          desaturated[idx + 0] = (unsigned char)r;
          desaturated[idx + 1] = (unsigned char)g;
          desaturated[idx + 2] = (unsigned char)b;
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
