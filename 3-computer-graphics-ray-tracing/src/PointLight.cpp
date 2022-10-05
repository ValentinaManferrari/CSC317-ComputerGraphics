#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
	d = (this->p - q).normalized(); // direction from point toward light as a vector
	max_t = (this->p - q).norm(); // parametric distance from q along d to light (may be inf)
	return;
  ////////////////////////////////////////////////////////////////////////////
}
