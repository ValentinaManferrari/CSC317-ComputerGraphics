#include "ray_intersect_box.h"
#include <iostream>
#include <vector>
#include <algorithm>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
    /* Reference Sources used to write this function:
         - Texbook Section 12.3.1: Bounding Boxes
             - Used algorithm from page 302 with a being the reciprocal of
               ray direction to avoid mathematical issues caused by zero division
         - Vector ausiliary functions
         https://stackoverflow.com/questions/9874802/how-can-i-get-the-maximum-or-minimum-value-in-a-vector
    */
    std::vector<double> tmin_list;
    std::vector<double> tmax_list;
    
    // loop through all 3 dimensions of the box (x,y,z)
    for (int axis = 0; axis < 3; axis++) {
        // bounds of the box on axis
        double min = box.min_corner(axis);
        double max = box.max_corner(axis);
        // retrieve ray information
        double e = ray.origin(axis);
        double direction = ray.direction(axis);
        // calculate tmax and tmin and store in array
        double a = 1 / direction;
        double tmin, tmax;
        if (a >= 0) {
            tmin = a * (min - e);
            tmax = a * (max - e);
        }
        else {
            tmin = a * (max - e);
            tmax = a * (min - e);
        }
        tmin_list.push_back(tmin);
        tmax_list.push_back(tmax);
    }
    double tmin = *std::max_element(std::begin(tmin_list), std::end(tmin_list));
    double tmax = *std::min_element(std::begin(tmax_list), std::end(tmax_list));
    
    // no intersection
    if (tmax < tmin) {
        return false;
    }
    // out of bounds
    if (tmax < min_t || tmin > max_t) {
        return false;
    } 
    // the ray intersects the box iff the intervals (t_xmin, t_xmax), (t_ymin, t_ymax), (t_zmin, t_zmax) overlap
    return true; 
  ////////////////////////////////////////////////////////////////////////////
}
