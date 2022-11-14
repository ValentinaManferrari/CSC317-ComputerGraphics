#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
	std::vector< std::vector<int> > VF; 
	vertex_triangle_adjacency(F, V.rows(), VF);

	N = Eigen::MatrixXd::Zero(V.rows(),3);
    for (int vertex = 0; vertex < V.rows(); vertex++) {
        // Iterate through all of the faces that have this vertex in common
        for (int face = 0; face < VF[vertex].size(); face++) {
            int triangle = VF[vertex][face];
            int a = F(triangle, 0);
            int b = F(triangle, 1);
            int c = F(triangle, 2);
            N.row(vertex) += triangle_area_normal(V.row(a), V.row(b), V.row(c));
        }
        // normalize N 
        N.row(vertex) = N.row(vertex).normalized();
    }
  ////////////////////////////////////////////////////////////////////////////
}
