#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
	// direction from point toward light as a vector.
	d = -(this->d).normalized();
	//parametric distance from q along d to light (by definition of Directional Light will be inf)
	max_t = std::numeric_limits<double>::infinity(); 
	return;
  ////////////////////////////////////////////////////////////////////////////
}

