#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  double red = r / 255.0;
  double green = g / 255.0;
  double blue = b / 255.0;

  double M = std::max({red, green, blue}); // get maximum rgb value
  double m = std::min({ red, green, blue }); // get minimum rgb value
  double C = M - m; // calculate the range

  v = M; // value

  // saturation
  if (v == 0) {
	  s = 0;
  }
  else {
	  s = C / v;
  }

  //hue
  if (M == red) {
	  h = 60 * (std::fmod((green - blue) / C, 6));
  }
  else if (M == green) {
	  h = 60 * (((blue - red) / C) + 2.0);
  }
  else if (M == blue) {
	  h = 60 * (((red - green) / C) + 4.0);
  }
  else {
	  h = 0;
  }

  // hue fitting into 360 degrees
  if (h >= 0) {
	  h = std::fmod(h, 360);
  }
  else {
	  h = h * (-1);
	  h = std::fmod(h, 360);
	  h = 360 - h;
  }
  ////////////////////////////////////////////////////////////////////////////
}
