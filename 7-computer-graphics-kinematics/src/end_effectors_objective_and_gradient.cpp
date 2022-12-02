#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // least-squares objective value
  f = [&](const Eigen::VectorXd & A)->double
  {
      Skeleton copy = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd tips = transformed_tips(copy, b);
      // Calculate total energy according to formula E(x_b) = ||(x_b - q)||^2
      return (tips - xb0).squaredNorm();
  };

  // least-squares objective gradient
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
      Skeleton copy = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd tips = transformed_tips(copy, b);
      // Calculate gradient accoridng to formula (dx/da)^T*(dE/dx)
      Eigen::MatrixXd J;
      kinematics_jacobian(copy, b, J); // using Kinematics_jacobian for dx/da
      return 2 * J.transpose() * (tips - xb0); // dE/dx just becomes (x_b - q)
  };

  // projects Euler angles to the constrained bone angles
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    // for every angle a_i do MAX[a_i_min , MIN[a_i_max, a_i]]
    for (int i = 0; i < skeleton.size(); i++) {
        A[i * 3 + 0] = std::max(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[3 * i + 0]));
        A[i * 3 + 1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[3 * i + 1]));
        A[i * 3 + 2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[3 * i + 2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
