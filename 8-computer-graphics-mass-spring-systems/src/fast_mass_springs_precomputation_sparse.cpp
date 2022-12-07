#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////    
      const int n = V.rows();
      std::vector<Eigen::Triplet<double> > ijv;
      std::vector<Eigen::Triplet<double> > ijv2;
      Eigen::SparseMatrix<double> Q(n, n);
  
      // List of edge lengths
      r = Eigen::VectorXd::Zero(E.rows());
      for (int i = 0; i < E.rows(); i++)
          r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();

      // M is a diagonal matrix of masses
      M.resize(n, n);
      for (int i = 0; i < n; i++) {
          ijv.emplace_back(i, i, m(i));
      }
      M.setFromTriplets(ijv.begin(), ijv.end());

      // Signed Indices Matrix gives A
      signed_incidence_matrix_sparse(n, E, A);

      // Construct C from variable name b (list of pinned vertices)
      C.resize(b.size(), n);
      for (int i = 0; i < b.size(); i++) {
          ijv2.emplace_back(i, b(i), 1);
      }
      C.setFromTriplets(ijv2.begin(), ijv2.end());
  
      // Computing Q 
      Q = k * A.transpose() * A + pow(delta_t, -2) * M + 1e10 * C.transpose() * C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
