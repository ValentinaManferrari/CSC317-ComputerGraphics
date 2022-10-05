#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
          int red = 0;
          int red_count = 0;

          int green = 0;
          int green_count = 0;

          int blue = 0;
          int blue_count = 0;
          
          // check immediate pixel neighbours
          for (int i = row - 1; i <= row + 1; i++) {
              for (int j = col - 1; j <= col + 1; j++) {

                  // making sure not to go out of bounds with corners and edge pixels
                  if (i>=0 && i<height && j>=0 && j<width) {
                      // record bayer pixel value
                      int value = bayer[j + width * i];

                      //check wich colour it is and add to approrpiate colour count
                      if ((i + 1) % 2 != 0) {
                          // odd column -> green pixel
                          if ((j + 1) % 2 != 0) {
                              green = green + value;
                              green_count++;
                          }
                          else { // even column -> blue pixel
                              blue = blue + value;
                              blue_count++;
                          }
                      }
                      // it means it's an even row therefore pattern red-green-red-green...
                      else {
                          // odd column -> red pixel
                          if ((j + 1) % 2 != 0) {
                              red = red + value;
                              red_count++;
                          }
                          else { // even column -> green pixel
                              green = green + value;
                              green_count++;
                          }
                      }

                      // include red value in rgb demosaic if there is any red 
                      if (red_count != 0) {
                          rgb[3 * (col + width * row) + 0] = red / red_count;
                      }
                      else { // otherwise set it to zero
                          rgb[3 * (col + width * row) + 0] = 0;
                      }
                      
                      // include green value in rgb demosaic if there is any green
                      if (green_count != 0) {
                          rgb[3 * (col + width * row) + 1] = green / green_count;
                      } 
                      else { // otherwise set it to zero
                          rgb[3 * (col + width * row) + 1] = 0;
                      }

                      // include blue value in rgb demosaic if there is any blue
                      if (blue_count != 0) {
                          rgb[3 * (col + width * row) + 2] = blue / blue_count;
                      }
                      else { // otherwise set it to zero
                          rgb[3 * (col + width * row) + 2] = 0;
                      }                     
                  }
              }
          }
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
