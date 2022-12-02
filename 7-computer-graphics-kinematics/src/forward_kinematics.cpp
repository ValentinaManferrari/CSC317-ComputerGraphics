#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d get_position(const int i, const Skeleton skeleton) {
    const int parent_idx = skeleton[i].parent_index;
    // Do nothing if bone is root
    if (parent_idx < 0) {
        return Eigen::Affine3d::Identity();
    }
    // For each bone, construct its transformation matrix recursively
    const Bone bone = skeleton[i];
    Eigen::Affine3d parent_position = get_position(parent_idx, skeleton);
    return Eigen::Affine3d(parent_position * bone.rest_T * euler_angles_to_transform(bone.xzx) * bone.rest_T.inverse());
}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
    T.resize(skeleton.size(), Eigen::Affine3d::Identity());
    // Loop result is a vector of matrices T, where matrix T[i] has the transformation matrix for bone i
    for (int i = 0; i < skeleton.size(); i++) {
        T[i] = get_position(i, skeleton);
    }
  /////////////////////////////////////////////////////////////////////////////
}
