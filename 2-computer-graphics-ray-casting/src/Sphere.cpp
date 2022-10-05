#include "Sphere.h"
#include "Ray.h"
#include <cmath>

bool Sphere::intersect(
    const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
    ////////////////////////////////////////////////////////////////////////////
    /* Reference Sources used to write this function:
          - Texbook Section 4.4: Ray-Object Intersection
              - Used Formulas from section 4.4.1: Ray-Sphere Intersection
    */
    // retrieve ray parameters
    Eigen::Vector3d e = ray.origin;
    Eigen::Vector3d d = ray.direction;
    // retrieve sphere values
    Eigen::Vector3d c = this->center;
    double r = this->radius;

    // Ray equation: f(p(t)) = 0 or f(e+t*d) = 0
    // Sphere Equation: (x - x_c)^2 + (y - y_c)^2 + (z - z_c)^2 - R^2 = 0

    // When two ray_eq and sphere_eq are combined --> [(d*d)]t^2 + [2d*(e - c)]t + [(e - c)*(e - c) - r^2] = 0 
    // Since all parameters are known exept t we need to solve --> At^2 + Bt + C = 0
    double A = d.dot(d);
    double B = 2 * d.dot(e - c);
    double C = (e - c).dot(e - c) - pow(r, 2);

    // Calculate discriminant --> B^2 - 4 * A * C
    double delta = pow(B, 2) - 4 * A * C;

    // if disciminant is negative then there is no intersection
    // if discriminant is zero it means there is only one point of intersection which means ray.origin is inside the object
    if (delta <= 0) {
        return false;
    }

    double t1 = (-B - sqrt(delta)) / (2 * A);
    double t2 = (-B + sqrt(delta)) / (2 * A);

    // if both points are less than min_t then it means they are behinf camera (do not consider)
    if (t1 < min_t && t2 < min_t) {
        return false;
    }
    else if (t1 < min_t && t2 > min_t) {
        t = t2;
    }
    else {
        t = t1;
    }

    // Vector p is the point of intersection
    Eigen::Vector3d p = e + t * d;
    // Normalize surface at point of intersection
    n = (p - c).normalized();

    return true;
    ////////////////////////////////////////////////////////////////////////////
}

