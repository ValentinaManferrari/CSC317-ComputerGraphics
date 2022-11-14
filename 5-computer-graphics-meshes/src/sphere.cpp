#include "sphere.h"
#include <iostream>
#include <math.h>
# define PI           3.14159265358979323846  /* pi */

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
         - https://en.wikipedia.org/wiki/Spherical_coordinate_system
  */
    
    int num_v = (num_faces_v + 1) * (num_faces_u + 1);
    int num_f = num_faces_v * num_faces_u;
   
    V.resize(num_v, 3);
    NV.resize(num_v, 3);
    UV.resize(num_v, 2);
    F.resize(num_f, 4);
    NF.resize(num_f, 4);
    UF.resize(num_f, 4);

    // polar angle increment value [0, pi]
    double theta_step = PI / num_faces_v; 
    // azimuthal angle increment value [0, 2pi]
    double phi_step = (2 * PI) / num_faces_u;  
    // Projection - split png equally lengthwise and widthwise
    double u_step = 1.0 / (num_faces_u + 1); 
    double v_step = 1.0 / (num_faces_v + 1); 

    // Calculate VERTEX info (V, UV, NV)
    for (int row = 0; row < num_faces_v + 1; row++) { 
        for (int col = 0; col < num_faces_u + 1; col++) { 
            double theta = row * theta_step;
            double phi = col * phi_step;
            // Conver each vertex coordinates from spherical to cartesian
            double x = cos(phi) * sin(theta);
            double y = sin(phi) * sin(theta);
            double z = cos(theta);
            // Calculate and store values into matrix
            int vertex = row * (num_faces_u + 1) + col;
            V.row(vertex) = Eigen::Vector3d(y, z, x);
            NV.row(vertex) = Eigen::Vector3d(y, z, x);
            // Calculate and stroe (u,v) mapping
            double u = u_step * col;
            double v = v_step * (num_faces_v + 1 - row);
            UV.row(vertex) = Eigen::Vector2d(u, v);
        }
    }

    // Calculate FACE info (F, UF, NF)
    for (int row = 0; row < num_faces_v; row++) {
        for (int col = 0; col < num_faces_u; col++) {
            // Calculating vertices of face
            int v1 = row * (num_faces_u + 1) + col;
            int v2 = row * (num_faces_u + 1) + col + 1;
            int v3 = (row + 1) * (num_faces_u + 1) + col + 1;
            int v4 = (row + 1) * (num_faces_u + 1) + col;
            // Storing in counterclokwise order starting from bottom-left vertext
            int face = row * num_faces_u + col;
            F.row(face) = Eigen::Vector4i(v1, v2, v3, v4);
            NF.row(face) = Eigen::Vector4i(v1, v2, v3, v4);
            UF.row(face) = Eigen::Vector4i(v1, v2, v3, v4);
        }
    }

  ////////////////////////////////////////////////////////////////////////////
}
