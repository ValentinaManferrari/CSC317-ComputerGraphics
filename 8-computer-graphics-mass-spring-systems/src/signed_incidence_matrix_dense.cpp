#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // A is (# edges) x (# vertices) matrix
  A = Eigen::MatrixXd::Zero(E.rows(),n);

  // For each edge, set A’s matrix value
  for (int i = 0; i < E.rows(); i++) {
      A(i, E(i, 0)) = 1;
      A(i, E(i, 1)) = -1;
  }
  //////////////////////////////////////////////////////////////////////////////
}
