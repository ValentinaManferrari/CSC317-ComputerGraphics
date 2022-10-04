#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
	/* Reference Sources used to write this function:
		  - Texbook Section 4.8: Ideal Specular Reflection
	*/
	Eigen::Vector3d reflectedRay = in - 2 * in.dot(n) * n;
	return reflectedRay.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
