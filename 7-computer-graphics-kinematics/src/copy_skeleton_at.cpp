#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  /////////////////////////////////////////////////////////////////////////////
    // Create a copy of a skeleton with joint angles set to A
    Skeleton copy = skeleton;
    
    // Mnually set each of the copied skeleton’s bones.xyx to the Euler angles listed in A
    for (int i = 0; i < skeleton.size(); i++) {
        double twist = A[i * 3 + 0];
        double bend = A[i * 3 + 1];
        double twist2 = A[i * 3 + 2];

        copy[i].xzx = Eigen::Vector3d(twist, bend, twist2);
    }

    return copy;
  /////////////////////////////////////////////////////////////////////////////
}
