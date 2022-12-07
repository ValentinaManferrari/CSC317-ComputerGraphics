#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
    // List of edge lengths
    r.resize(E.rows());
    for (int i = 0; i < E.rows(); i++) {
        r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
    }

    // M is a diagonal matrix of masses
    M = Eigen::MatrixXd::Zero(V.rows(), V.rows());
    for (int i = 0; i < V.rows(); i++) {
        M(i, i) = m(i);
    }

    // Signed Indices Matrix gives A
    signed_incidence_matrix_dense(V.rows(), E, A);
    
    // Construct C from variable name b (list of pinned vertices)
    C = Eigen::MatrixXd::Zero(b.size(), V.rows());
    for (int i = 0; i < b.size(); i++) {
        C(i, b(i)) += 1;
    }

    // Computing Q 
	Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());
    Q = k * A.transpose() * A + pow(delta_t, -2) * M + 1e10 * C.transpose() * C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
