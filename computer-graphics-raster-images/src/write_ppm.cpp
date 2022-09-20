#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - https://en.wikipedia.org/wiki/Netpbm#File_format_description 
        - https://cplusplus.com/forum/general/208835/
        - https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
  */

  // open ppm file
  std::ofstream ppm_file(filename);
  
  if (ppm_file.is_open()) {
      // add header : P3, width, height, max intensity (255 for rgb || 1 for grayscale)
      ppm_file << "P3 " + std::to_string(width) + " " + std::to_string(height) + " 255" << std::endl;

      // add data
      int img_size = width * height * num_channels;
      for (int i = 0; i < img_size; ++i) {
          
          ppm_file << (unsigned int) data[i];
          // if it's a grayscale img repeate the same value 3 times 
          if (num_channels == 1) {
              ppm_file << " " << (unsigned int)data[i] << " " << (unsigned int)data[i];
          }
          // check the approptiate spacing 
          if ( (i+1) % 3 == 0) {
              ppm_file << "   "; // add double spacing every pixel value (= channel value *3)
          }
          else if (i % (width * num_channels) == 0) {
              ppm_file << std::endl; // new line at the end of each row
          }
          else {
              ppm_file << " "; // add single space between channel values
          }
      }
      
      // close file
      ppm_file.close();
      return true;
  }
  else {
      std::cout << "Error: could not open file" << filename << std::endl;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
