#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
    /* Reference Sources used to write this function:
        - Texbook Section 4.3.2: Perspective Views
    */

    // Compute u and v using textboom formula (4.1)
    // u = l + (r - l)(i + 0.5) / n_x;
    double u = -camera.width / 2 + camera.width * (i + 0.5) / width;

    // v = b + (t - b)(j + 0.5) / n_y;
    double v = -camera.height / 2 + camera.height * (j + 0.5) / height;

    // Ray Direction <-- uU + vV -dW 
    ray.direction = Eigen::Vector3d(u * camera.u + v * camera.v - camera.d * camera.w );
    
    // Ray Origin <-- e
    ray.origin = camera.e;

  ////////////////////////////////////////////////////////////////////////////
}

