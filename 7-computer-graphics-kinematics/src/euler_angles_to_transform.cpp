#include "euler_angles_to_transform.h"

# define PI           3.14159265358979323846  /* pi */

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  
	// Convert to radians because that's what AngleAxis expects
	double theta1 = xzx[0] * (PI / 180.0);
	double theta2 = xzx[1] * (PI / 180.0);
	double theta3 = xzx[2] * (PI / 180.0);

	// Create the rotation matricies for Twist-Bend-Twist 
	Eigen::Affine3d Rx, Ry, Rz;
	Rx = Eigen::AngleAxisd(theta1, Eigen::Vector3d::UnitX());
	Ry = Eigen::AngleAxisd(theta2, Eigen::Vector3d::UnitZ());
	Rz = Eigen::AngleAxisd(theta3, Eigen::Vector3d::UnitX());

	return Eigen::Affine3d(Rz * Ry * Rz);
  /////////////////////////////////////////////////////////////////////////////
}
