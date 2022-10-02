#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
	d = -(this->d).normalized(); // direction from point toward light as a vector.
	max_t = std::numeric_limits<double>::infinity(); //parametric distance from q along d to light (by definition of Directional Light will be inf)
	return;
  ////////////////////////////////////////////////////////////////////////////
}

