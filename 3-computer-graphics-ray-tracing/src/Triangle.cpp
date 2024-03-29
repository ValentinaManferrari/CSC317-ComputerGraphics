#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
          - Texbook Section 4.4: Ray-Object Intersection
              - Used Formulas from section 4.4.2: Ray-Triangle Intersection
  */
  // retrieve ray parameters
    Eigen::Vector3d eye = ray.origin;
    Eigen::Vector3d direction = ray.direction;

    // retrieve triangle corner values
    Eigen::Vector3d A = std::get<0>(this->corners);
    Eigen::Vector3d B = std::get<1>(this->corners);
    Eigen::Vector3d C = std::get<2>(this->corners);

    double a = A[0] - B[0];
    double b = A[1] - B[1];
    double c = A[2] - B[2];
    double d = A[0] - C[0];
    double e = A[1] - C[1];
    double f = A[2] - C[2];
    double g = direction[0];
    double h = direction[1];
    double i = direction[2];
    double j = A[0] - eye[0];
    double k = A[1] - eye[1];
    double l = A[2] - eye[2];

    double m = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

    t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / m;

    if (t < min_t) {
        return false;
    }

    double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / m;
    if (gamma < 0 || gamma > 1) {
        return false;
    }

    double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / m;
    if (beta < 0 || beta >(1 - gamma)) {
        return false;
    }

    n = (B - A).cross(C - A).normalized();
    return true;
  ////////////////////////////////////////////////////////////////////////////
}


