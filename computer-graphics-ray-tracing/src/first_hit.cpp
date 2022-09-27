#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
        - Texbook Section 4.4: Ray-Object Intersection
            - Used Algorithm from section 4.4.4: Intersection a Group of Objects
        -
  */
    bool hit = false;       // Flag recording wether the ray hits an object

    // Keep track of the closest hit found so far, when no object is hit yet distance is +infinity
    double closest_hit = std::numeric_limits<double>::infinity();
    double hit_t;           // Store t value returned from intersect
    Eigen::Vector3d hit_n;  // Store normal value returned from intersect

    // For each object i in the group
    for (int i = 0; i < objects.size(); i++) {

        // check if the ray intersect with object i
        bool intersection_check = objects[i]->intersect(ray, min_t, hit_t, hit_n);

        // if ray intersects object AND it's the new closest object it hits
        if (intersection_check && hit_t < closest_hit) {
            // then update the closest hit parameters
            hit_id = i;
            t = hit_t;
            n = hit_n;
            closest_hit = t;
            // and turn on hit flag
            hit = true;
        }
    }
    return hit;
  ////////////////////////////////////////////////////////////////////////////
}
