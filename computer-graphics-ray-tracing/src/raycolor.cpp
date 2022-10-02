#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  rgb = Eigen::Vector3d(0,0,0); //default is black

  //constants
  double const epsilon = 1e-6; //offset
  int const max_depth = 5; // maximum number of allowed function calls

  int hit_id;
  double t;
  Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);

  if (hit) {
      rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
      Eigen::Vector3d km = objects[hit_id]->material->km; // mirror coefficient

      if (num_recursive_calls < max_depth && !km.isZero(epsilon)) {
          Ray reflectedRay;
          reflectedRay.origin = ray.origin + t * ray.direction;
          reflectedRay.direction = reflect(ray.direction, n).normalized();

          Eigen::Vector3d colour;
          bool rayColour = raycolor(reflectedRay, epsilon, objects, lights, num_recursive_calls + 1, colour);
          
          if (rayColour) {
              rgb += (colour.array() * km.array()).matrix();
          }
      }
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
