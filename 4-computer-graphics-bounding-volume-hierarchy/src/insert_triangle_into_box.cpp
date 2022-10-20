#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
	// loop through all 3 dimensions of the box (x,y,z)
	for (int axis = 0; axis < 3; axis++) {
		B.min_corner[axis] = std::min({ B.min_corner[axis], a[axis], b[axis], c[axis] });
		B.max_corner[axis] = std::max({ B.max_corner[axis], a[axis], b[axis], c[axis] });
	}
	return;
  ////////////////////////////////////////////////////////////////////////////
}


