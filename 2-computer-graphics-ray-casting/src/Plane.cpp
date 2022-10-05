#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	  // retrieve ray parameters
	Eigen::Vector3d e = ray.origin;
	Eigen::Vector3d d = ray.direction;
	// retrieve plane values
	Eigen::Vector3d N = this->normal;
	Eigen::Vector3d p0 = this->point;

	// t = (plane*(e - pt)) / (plane * d) 
	double denom = N.dot(d);
	
	// if denominator is zero ray is not hitting the plane
	if (denom == 0) {
		return false;
	}

	t = -N.dot(e - p0) / denom;
	n = N.normalized();
	
	if (t < min_t) {
		return false;
	}
	return true;
  ////////////////////////////////////////////////////////////////////////////
}

