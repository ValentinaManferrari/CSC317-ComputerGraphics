#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - https://en.wikipedia.org/wiki/Bayer_filter
        - "In this assignment, we'll assume the top left pixel is green, its right neighbor is blue 
            and neighbor below is red, and its kitty-corner neighbor is also green."
  */

  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
          int idx = col + width * row;
          int channel;
          // odd rows have pattern green-blue-green-blue...
          if ((row+1) % 2 != 0) {
              // odd column -> green pixel
              if ((col+1) % 2 != 0) {
                  channel = 1;
              }
              else { // even column -> blue pixel
                  channel = 2;
              }
          }
          // it means it's an even row therefore pattern red-green-red-green...
          else {
              // odd column -> red pixel
              if ((col + 1) % 2 != 0) {
                  channel = 0;
              }
              else { // even column -> green pixel
                  channel = 1;
              }
          }
          bayer[idx] = rgb[3 * idx + channel];
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
