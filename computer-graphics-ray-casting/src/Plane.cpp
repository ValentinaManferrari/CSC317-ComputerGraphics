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
	Eigen::Vector3d plane = this->normal;
	Eigen::Vector3d pt = this->point;

	// t = (plane*(e - pt)) / (plane * d) 
	double denom = plane.dot(d);
	
	// if denominator is zero ray is not hitting the plane
	if (denom == 0) {
		return false;
	}

	t = plane.dot(e - pt) / denom;
	n = plane.normalized();
	
	if (t >= min_t) {
		return true;
	}
	return false;
  ////////////////////////////////////////////////////////////////////////////
}

