#include "catmull_clark.h"
#include "vertex_triangle_adjacency.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <functional>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
         - Lecture 5 slides 60-67
         - https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
  */
    
    if (num_iters == 0) {
        return;
    }

    // Initialize data structures
    std::vector<std::pair<int, int>> E;     	// vector of edges pairs
    std::vector<std::pair<int, int>> FE;    	// Edge Neighbour faces
    std::vector<std::unordered_set<int>> VV;    // Vertex neigbhour vertices
    VV.resize(V.rows());
    
    // Get all edges in mesh
    for (int face = 0; face < F.rows(); face++) {
        for (int corner = 0; corner < F.cols(); corner++) {

            int v0 = F(face, corner);
            int v1 = F(face, (corner + 1) % 4);
            int v2 = F(face, (corner + 3) % 4);
            auto forward_edge = std::make_pair(v0, v1);
            auto backward_edge = std::make_pair(v1, v0);

            VV[v0].insert(v1);
            VV[v0].insert(v2);

            bool exist = false;
            for (int edge = 0; edge < E.size(); edge++) {
                if (E[edge] == forward_edge || E[edge] == backward_edge) {
                    exist = true;
                    FE[edge] = std::make_pair(FE[edge].first, face);
                    break;
                }
            }
            if (!exist) {
                E.push_back(forward_edge);
                FE.push_back(std::make_pair(face, -1));
            }
        }
    }
   
    // Resize outputs
    SV.resize(V.rows() + F.rows() + E.size(), 3);
    SF.resize(F.rows() * F.cols(), 4);
    
    int sv_row = 0;
    std::vector<Eigen::RowVector3d> face_points;
    std::vector<Eigen::RowVector3d> edge_points;

    // STEP 1: For each face, add a face point
    // Set each face point to be the average of all original points for the respective face
    int face_point_offset = sv_row;
    for (int face = 0; face < F.rows(); face++) {
        Eigen::RowVector3d average(0.0, 0.0, 0.0);
        for (int corner = 0; corner < F.cols(); corner++) {
            average += V.row(F(face, corner));
        }
        average = average / (double)F.cols();
        face_points.push_back(average);
        SV.row(sv_row++) << average;
    }

    // STEP 2: For each edge, add an edge point
    // Set each edge point to be the average of the two neighbouring face points (AF) 
    // and the midpoint of the edge (ME) = (AF+ME)/2
    int edge_point_offset = sv_row;
    for (int face = 0; face < E.size(); face++) {
        Eigen::RowVector3d average(0.0, 0.0, 0.0);
        average += V.row(E[face].first) + V.row(E[face].second);
        average += face_points[FE[face].first] + face_points[FE[face].second];
        average = average / 4.0;
        edge_points.push_back(average);
        SV.row(sv_row++) << average;
    }

    // STEP3: For each original point P, take the average F of all n (recently created) face points for faces 
    // touching P, and take the average R of all n edge midpoints for (original) edges touching P, where 
    // each edge midpoint is the average of its two endpoint vertices (not to be confused with new "edge points" above). 
    //  - Move each original point to the new vertex point -> (F+2R+(n-3)P)/n
    //    (This is the barycenter of P, R and F with respective weights (n ? 3), 2 and 1)
    //  

    // STEP 4: Form edges and faces in the new mesh
    //  - Connect each new face point to the new edge points of all original edges defining the original face
    //  - Connect each new vertex point to the new edge points of all original edges incident on the original vertex
    //  - Define new faces as enclosed by edges
   
    // Recursively call catmull_clark until num_iters becomes zero
    Eigen::MatrixXd new_SV;
    Eigen::MatrixXi new_SF;
    catmull_clark(SV, SF, num_iters - 1, new_SV, new_SF);

  ////////////////////////////////////////////////////////////////////////////
}
