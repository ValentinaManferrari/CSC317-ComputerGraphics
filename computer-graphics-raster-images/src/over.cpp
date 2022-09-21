#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - https://en.wikipedia.org/wiki/Alpha_compositing
  */
  
  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
          int idx = 4 * (col + row * width); // dealing with 4 channels now - adding alpha 
          // calculate alpha value for each img vector
          double alpha_a = A[idx + 3] / 255.0;
          double alpha_b = B[idx + 3] / 255.0;
          double alpha_c = alpha_a + (1 - alpha_a)*alpha_b;

          C[idx + 3] = (unsigned char) alpha_c * 255;

          for (int rgb = 0; rgb < 3; rgb++) {
              double c_a = A[idx + rgb];
              double c_b = B[idx + rgb];
              C[idx + rgb] = (unsigned char)((c_a * alpha_a) + (c_b * alpha_b * (1 - alpha_a))) / alpha_c;
          }
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
