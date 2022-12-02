#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
    const double max_step = 10000.0;
    
    for (int i = 0; i < max_iters; i++) {
        // grad_f gives dE/da
        Eigen::VectorXd gradient = grad_f(z);
        // Use line_search to find sigma
        double sigma = line_search(f, proj_z, z, gradient, max_step);
        z -= sigma * gradient;
        // Project at the end to make sure our constraints are satisfied
        proj_z(z);
    }
  /////////////////////////////////////////////////////////////////////////////
}
