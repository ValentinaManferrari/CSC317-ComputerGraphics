#include "rgba_to_rgb.h"

void rgba_to_rgb(
const std::vector<unsigned char> & rgba,
const int & width,
const int & height,
std::vector<unsigned char> & rgb)
{
rgb.resize(height*width*3);
////////////////////////////////////////////////////////////////////////////
int rgb_idx = 0;
for (int rgba_idx = 0; rgba_idx < rgba.size(); ++rgba_idx) {
	if ((rgba_idx + 1) % 4) {
		continue; // skip alpha channel 
	}
	else {
		rgb[rgb_idx] = rgba[rgba_idx]; //add RGB channels
		++ rgb_idx;
	}
}
////////////////////////////////////////////////////////////////////////////
}
