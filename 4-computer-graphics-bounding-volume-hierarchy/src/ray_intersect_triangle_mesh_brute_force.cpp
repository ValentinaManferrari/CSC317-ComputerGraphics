#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
    bool hit_found = false;
    hit_t = std::numeric_limits<double>::infinity();
    double new_hit_t = 0.0;
    // loop through all triangles in mesh
    for (int i = 0; i < F.rows(); i++) {
        // get triangle vertices
        Eigen::RowVector3d A = V.row(F(i, 0));
        Eigen::RowVector3d B = V.row(F(i, 1));
        Eigen::RowVector3d C = V.row(F(i, 2));
        // check for intersection
        bool intersection = ray_intersect_triangle(ray, A, B, C, min_t, max_t, new_hit_t);
        if (intersection && new_hit_t < hit_t) {
            hit_t = new_hit_t;
            hit_f = i;
            hit_found = true;
        }
    }
    return hit_found;
  ////////////////////////////////////////////////////////////////////////////
}
