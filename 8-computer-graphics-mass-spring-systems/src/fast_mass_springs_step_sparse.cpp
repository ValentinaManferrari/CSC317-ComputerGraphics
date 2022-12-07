#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
    Eigen::MatrixXd d(E.rows(), 3);
    Eigen::MatrixXd y(V.rows(), 3);
    Eigen::MatrixXd B(V.rows(), 3);

    // "local-global" iterative algorithm:
    for (int iter = 0; iter < 50; iter++){
        
        // Local Step: : given current values of p determine d_ij for each spring
        for (int i = 0; i < r.size(); i++) {
            d.row(i) = r(i) * (Unext.row(E(i, 0)) - Unext.row(E(i, 1))).normalized(); 
        }
        // Global Step:  given all d_ij vectors, find positions that minimize quadratic energy
        y = pow(delta_t, -2) * M * (2 * Ucur - Uprev) + fext;
        B = k * A.transpose() * d + y + 1e10 * C.transpose() * C * V;
        Unext = prefactorization.solve(B);
    }
  //////////////////////////////////////////////////////////////////////////////
}
