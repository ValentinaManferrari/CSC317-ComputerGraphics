#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  int size = (width * height) * 3; // multiplying by 3 channels because we know it's a rgb img
  int i = 0;

  while(i < size) { 
	  // reading colour values from rgb vector
	  float red = rgb[i];
	  float green = rgb[i+1];
	  float blue = rgb[i+2];

	  // converting to gray using given weighted average
	  gray[i/3] = (unsigned char)(0.2126*red + 0.7152*green + 0.0722*blue);

	  i = i + 3; // Note: loop step is 3 for handling channels 
  }
  ////////////////////////////////////////////////////////////////////////////
}


