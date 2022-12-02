#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
    U.resize(V.rows(), V.cols());

    for (int i = 0; i < V.rows(); i++) {
        Eigen::Vector4d pose = Eigen::Vector4d::Zero();  
        
        for (int j = 0; j < skeleton.size(); j++) {
            if (skeleton[j].weight_index >= 0) {
                // For every vertex, find its transformed coordinate by summing the weighted contributions of all the bones
                pose += W(i, skeleton[j].weight_index) * (T[j] * Eigen::Vector4d(V(i, 0), V(i, 1), V(i, 2), 1));
            }
        }
        U(i, 0) = pose(0);
        U(i, 1) = pose(1);
        U(i, 2) = pose(2);
    }
  /////////////////////////////////////////////////////////////////////////////
}
