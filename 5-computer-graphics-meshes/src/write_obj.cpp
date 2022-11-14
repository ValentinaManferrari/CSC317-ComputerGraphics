#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  /* Reference Sources used to write this function:
         - https://en.wikipedia.org/wiki/Wavefront_.obj_file
  */

  std::ofstream obj(filename);
  // if cannot open file return an error
  if (!obj.is_open()) {
      std::cout << "ERROR: cannot open file '" << filename << "'" << std::endl;
      return false;
  }

  // Vertex positions
  for (int i = 0; i < V.rows(); i++) {
      obj << "v " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << std::endl;
  }

  // Texture coordinates
  for (int i = 0; i < UV.rows(); i++) {
      obj << "vt " << UV(i, 0) << " " << UV(i, 1) << std::endl;
  }

  // Normals
  for (int i = 0; i < NV.rows(); i++) {
      obj << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << std::endl;
  }

  // Faces
  for (int i = 0; i < F.rows(); i++) {
      obj << "f ";
      // Faces are defined using lists of vertex, textureand normal indices 
      for (int j = 0; j < F.cols(); j++) {
          // in the format <vertex_index> / <texture_index> / <normal_index>
          obj << F(i, j) + 1 << "/" << UF(i, j) + 1 << "/" << NF(i, j) + 1 << " "; 
      }
      obj << std::endl;
  }

  obj.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
