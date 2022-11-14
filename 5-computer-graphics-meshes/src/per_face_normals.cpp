#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  N = Eigen::MatrixXd::Zero(F.rows(),3);

  for (int face = 0; face < F.rows(); face++) {
      int a = F(face, 0);
      int b = F(face, 1);
      int c = F(face, 2);
      N.row(face) = triangle_area_normal(V.row(a), V.row(b), V.row(c));
  }
  ////////////////////////////////////////////////////////////////////////////
}
