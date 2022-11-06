#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
      - Lecture 4 Slides (#32)
      - StackOverflow resources: https://stackoverflow.com/questions/7113344/find-whether-two-triangles-intersect-or-not/7126909#7126909
  */
    double t;

    // Make each of Triangle A edges a "ray" 
    Ray ray_A0 = Ray(A0, A1 - A0);
    Ray ray_A1 = Ray(A1, A2 - A1);
    Ray ray_A2 = Ray(A2, A0 - A2);
    // Check if rays hit triangle B
    bool intersect_A0 = ray_intersect_triangle(ray_A0, B0, B1, B2, 0, 1, t);
    bool intersect_A1 = ray_intersect_triangle(ray_A1, B0, B1, B2, 0, 1, t);
    bool intersect_A2 = ray_intersect_triangle(ray_A2, B0, B1, B2, 0, 1, t);
    
    // Make each of Triangle B edges a "ray" 
    Ray ray_B0 = Ray(B0, B1 - B0);
    Ray ray_B1 = Ray(B1, B2 - B1);
    Ray ray_B2 = Ray(B2, B0 - B2);
    // Check if rays hit triangle A
    bool intersect_B0 = ray_intersect_triangle(ray_B0, A0, A1, A2, 0, 1, t);
    bool intersect_B1 = ray_intersect_triangle(ray_B1, A0, A1, A2, 0, 1, t);
    bool intersect_B2 = ray_intersect_triangle(ray_B2, A0, A1, A2, 0, 1, t);

    // if there is any hit return true
    if (intersect_A0 || intersect_A1 || intersect_A2 || intersect_B0 || intersect_B1 || intersect_B2) {
        return true;
    }
    return false;
  ////////////////////////////////////////////////////////////////////////////
}
