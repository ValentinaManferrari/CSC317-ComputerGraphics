#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <math.h>
# define PI           3.14159265358979323846  /* pi */

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  std::vector< std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  double eps = cos((PI * corner_threshold) / 180);
  
  // For each face (1) calculate normal vector
  for (int face = 0; face < F.rows(); face++) {
      Eigen::RowVector3d a = V.row(F(face, 0));
      Eigen::RowVector3d b = V.row(F(face, 1));
      Eigen::RowVector3d c = V.row(F(face, 2));
      Eigen::RowVector3d norm = triangle_area_normal(a, b, c);

      // Go through each neighbour corner 
      for (int corner = 0; corner < 3; corner++) {
          std::vector<int> neighbours = VF[F(face, corner)];
          Eigen::RowVector3d n(0, 0, 0);

          // Go through neighbor faces and (2) calculate their norms
          for (int i = 0; i < neighbours.size(); i++) {
              int neighbour_face = neighbours[i];
              Eigen::RowVector3d A = V.row(F(neighbour_face, 0));
              Eigen::RowVector3d B = V.row(F(neighbour_face, 1));
              Eigen::RowVector3d C = V.row(F(neighbour_face, 2));
              Eigen::RowVector3d neighbour_norm = triangle_area_normal(A, B, C);
              // Add neigbour norm if (2)*(1) is greater than epsilon
              if (neighbour_norm.normalized().dot(norm.normalized()) > eps) {
                  n += neighbour_norm;
              }
          }
          // Add corner normal to list
          N.row(face * 3 + corner) = n.normalized();
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
