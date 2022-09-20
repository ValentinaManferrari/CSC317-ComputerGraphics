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
  */

  // open ppm file
  std::ofstream ppm_file(filename);
  // add header : P6, width, height, num_channels
  if (ppm_file.is_open()) {
      // add data
      // close file
      return true;
  }
  else {
      std::cout << "Error: could not open file" << filename << std::endl;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
