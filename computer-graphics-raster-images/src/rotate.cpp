#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  int row = 0;
  while(row < height) {
      int rotated_col = row;  
      int start = width - 1;
      int end = 0;
      while (start > end) {
          int rotated_row = width - start - 1;
          for (int rgb = 0; rgb < num_channels; rgb++) {
              rotated[(rotated_col + height*rotated_row)*num_channels + rgb] = input[num_channels * (start + width * row) + rgb];
          }
          start--;
          end++;
      };
      row++;
  }
  ////////////////////////////////////////////////////////////////////////////
}
