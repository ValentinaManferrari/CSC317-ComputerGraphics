#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
    for (int axis = 0; axis < 3; axis++) {
        // Boxes will not intersect if they don't intersect in all axis 
        if (A.min_corner[axis] > B.max_corner[axis] || A.max_corner[axis] < B.min_corner[axis]) {
            return false;
        }
    }
    return true;
  ////////////////////////////////////////////////////////////////////////////
}

