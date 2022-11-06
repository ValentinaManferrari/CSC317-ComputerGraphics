#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // loop through all 3 dimensions of the box (x,y,z)
    for (int axis = 0; axis < 3; axis++) {
        B.min_corner[axis] = std::min(A.min_corner[axis], B.min_corner[axis]);
        B.max_corner[axis] = std::max(A.max_corner[axis], B.max_corner[axis]);
    }
    return;
  ////////////////////////////////////////////////////////////////////////////
}

