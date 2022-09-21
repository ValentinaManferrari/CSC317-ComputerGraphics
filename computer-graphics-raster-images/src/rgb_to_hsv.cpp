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
  double M = std::max({ r, g, b }); // get maximum rgb value
  double m = std::min({ r, g, b }); // get minimum rgb value
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
  if (M == r) {
	  h = 60 * std::fmod((g - b) / C, 6);
  }
  else if (M == g) {
	  h = 60 * ((b - r) / C) + 2;
  }
  else if (M == b) {
	  h = 60 * ((r - g) / C) + 4;
  }
  else {
	  h = 0; // hue is undefined
  }

  // hue fitting into 360 degrees
  if (h > 0) {
	  h = std::fmod(h, 360);
  }
  else {
	  h = h * (-1); 
	  h = std::fmod(h, 360);
	  h = 360 - h;
  }

  ////////////////////////////////////////////////////////////////////////////
}
