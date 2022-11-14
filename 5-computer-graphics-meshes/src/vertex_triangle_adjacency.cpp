#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  for (int face = 0; face < F.rows(); face++) {
      for (int corner = 0; corner < F.cols(); corner++) {
          int vertex = F(face, corner);
          VF[vertex].push_back(face);
      }
  }
   ////////////////////////////////////////////////////////////////////////////
}

