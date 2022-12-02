#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  const double h = 1.0e-7;
  Skeleton copy = skeleton;

  Eigen::VectorXd tips = transformed_tips(skeleton, b);
  Eigen::VectorXd trans_tips;

  J = Eigen::MatrixXd::Zero(b.size()*3, skeleton.size()*3);
 
  // Measure the effect of a rotation of the jth bone on the ith bone
  for (int i = 0; i < skeleton.size(); i++) {
      for (int j = 0; j < 3; j++) {
          // Take an epsilon step up and down
          copy[i].xzx(j) += h;
          trans_tips = transformed_tips(copy, b);
          copy[i].xzx(j) -= h;  
      
          J.col(3 * i + j) = (trans_tips - tips) / h;
      }
  }
  /////////////////////////////////////////////////////////////////////////////
}
