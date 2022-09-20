#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  /* Reference code used :
  *		- https://pencilprogrammer.com/cpp-programs/reverse-array/
  */
  int row_count = 0;
  // iterate through each row separately
  while( row_count < height ) {
	  // define the row's start and end pixels (reading from left to right)
	  int start = 0; 
	  int end = width - 1; 
	  // 
	  while (start <= end) {
		  for (int rgb = 0; rgb < num_channels; rgb++) { //keep channel values in the right order e.g. {255 0 0  0 255 50  20 30 100} becomes {20 30 100  0 255 50  255 0 0}	
			  reflected[(start + width*row_count)*num_channels + rgb] = input[(end + width*row_count)*num_channels + rgb];
			  reflected[(end + width*row_count)*num_channels + rgb] = input[(start + width*row_count)*num_channels + rgb];
		  }
		  start++;
		  end--;
	  }
	  row_count++;
  }
  ////////////////////////////////////////////////////////////////////////////
}
