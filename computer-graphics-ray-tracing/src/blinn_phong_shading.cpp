#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
          - Texbook Section 4.5.4: Multiple Point Lights
  */
    
  Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0); // Start from black

  // Get all needed coefficients
  Eigen::Vector3d ka = objects[hit_id]->material->ka; // ambient
  Eigen::Vector3d kd = objects[hit_id]->material->kd; // diffuse
  Eigen::Vector3d ks = objects[hit_id]->material->ks; // specular
  double const epsilon = 1e-6; // offset
  double p = objects[hit_id]->material->phong_exponent; // Phong exponent

  // Add ambient light as first thing
  Eigen::Vector3d ambient_intensity = Eigen::Vector3d(0.1, 0.1, 0.1); 
  rgb += (ka.array() * ambient_intensity.array()).matrix();

  // Compute viewing ray
  Ray toLight;
  toLight.origin = ray.origin + (t * ray.direction) + (n * epsilon);
  double t_max;

  // For each light calculate diffuse and specular components and add them to total rgb
  for (int i = 0; i < lights.size(); i++) {
      
      lights[i]->direction(toLight.origin, toLight.direction, t_max);

      int new_hit_id;
      double new_t;
      Eigen::Vector3d new_n;
      bool hit = first_hit(toLight, epsilon, objects, new_hit_id, new_t, new_n);
      
      // If we hit object it means point is in shadow
      if (hit && new_t < t_max) {
          continue;
      }

      // Get light intensity and calculate the half vector
      Eigen::Vector3d I = lights[i]->I;
      Eigen::Vector3d h = (-ray.direction.normalized() + toLight.direction).normalized();
        
      // Calculate Lambertian and Blinn-Phong Shading using textbook eq. 4.5.1 and 4.5.2
      Eigen::Vector3d diffuse = std::max(0.0, n.dot(toLight.direction)) * (kd.array() * I.array()).matrix();
      Eigen::Vector3d specular = std::pow(std::max(0.0, n.dot(h)), p) * (ks.array() * I.array()).matrix();
        
      // Add both diffuse and specular components to rgb
      rgb += (diffuse + specular); 
  }

  rgb = rgb.cwiseMin(1.0); // Make sure rgb does not exceed maximum of 1 (clip)
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
