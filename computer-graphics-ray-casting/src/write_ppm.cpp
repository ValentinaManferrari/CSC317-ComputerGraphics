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
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - https://en.wikipedia.org/wiki/Netpbm#File_format_description
        - https://cplusplus.com/forum/general/208835/
        - https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
  */

  // open ppm file
    std::ofstream ppm_file(filename);

    if (ppm_file.is_open()) {
        // defin magic number based on number of channels
        std::string magic_number = "P2";
        if (num_channels == 3) {
            magic_number = "P3";
        }

        // add header : magic number, width, height, max intensity (255 for rgb || 1 for grayscale)
        // ppm_file << "P3 " + std::to_string(width) + " " + std::to_string(height) + " 255" << std::endl;
        ppm_file << magic_number << std::endl;
        ppm_file << width << " " << height << std::endl;
        ppm_file << 255 << std::endl;

        // add data
        int img_size = width * height * num_channels;
        for (int i = 0; i < img_size; ++i) {

            ppm_file << (unsigned int)data[i];

            // check the approptiate spacing 
            if ((i + 1) % (width * num_channels) == 0) {
                ppm_file << std::endl; // new line at the end of each row
            }
            else if ((i + 1) % num_channels == 0) {
                ppm_file << "   "; // add double spacing every pixel value (= channel value *3)
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
