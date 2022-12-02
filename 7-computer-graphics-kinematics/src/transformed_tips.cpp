#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
	std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;
	// Use forward_kinematics to find the transformation matrices T
	forward_kinematics(skeleton, T);

	Eigen::Vector4d tip = Eigen::Vector4d::Zero();
	Eigen::VectorXd tips(b.size() * 3);
	
	// Compose bone i’s T with bone i’s rest_T to get the transformation acting on the canonical bone
	for (int i = 0; i < b.size(); i++) {
		tip = T[b[i]] * skeleton[b[i]].rest_T * Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);
		tips[i * 3] = tip.x() / tip.w();
		tips[i * 3 + 1] = tip.y() / tip.w();
		tips[i * 3 + 2] = tip.z() / tip.w();
	}

	// Output is a (3 * n length) stacked vector of n bone tip positions indexed by b
	return tips;
  /////////////////////////////////////////////////////////////////////////////
}
