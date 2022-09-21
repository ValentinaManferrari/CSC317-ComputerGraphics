#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
          // reading colour values from rgb vector
          int red = rgb[0 + 3 * (col + row * width)];
          int green = rgb[1 + 3 * (col + row * width)];
          int blue = rgb[2 + 3 * (col + row * width)];
          // converting to gray using a weighted average
          gray[col + row*width] = 0.2126*red + 0.7152*green + 0.0722*blue;
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}


