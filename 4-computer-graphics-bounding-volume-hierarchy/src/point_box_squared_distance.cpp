#include "point_box_squared_distance.h"
#include <cmath>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
    
    double distance = 0.0;

    for (int axis = 0; axis < 3; axis++) {
        // If inside the box, distance is zero so skip
        if (query[axis] >= box.min_corner[axis] && query[axis] <= box.max_corner[axis]) {
            continue;  
        }
        // Max corner is the closest 
        else if (query[axis] > box.max_corner[axis]) {
            distance += pow(query[axis] - box.max_corner[axis], 2); // add squared distance along the axis
        }
        // Min corner is the closest 
        else {
            distance += pow(box.min_corner[axis] - query[axis], 2); // add squared distance along the axis     
        }
    }
    return distance;
  ////////////////////////////////////////////////////////////////////////////
}
