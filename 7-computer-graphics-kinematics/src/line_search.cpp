#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
    // Start with sigma=max_step, keep halving until we find the energy is decreasing
    double sigma = max_step; 
    Eigen::VectorXd delta_z = z - max_step * dz;  
    proj_z(delta_z);

    // Using f from end_effectors_objective_and_gradient to compute energies
    double base_energy = f(z);
    double delta_energy = f(delta_z); 
    
    // We are looking for a sigma that satisfies E(proj(a+sigma* delta a) < E(a)
    // Added maximum iteration condition to break, in case we never find a decreasing energy.
    int iterations = 0;
    while (delta_energy > base_energy && iterations < 40) {
        sigma = sigma / 2;
        delta_z = z - sigma * dz;
        proj_z(delta_z);
        delta_energy = f(delta_z);
        iterations++;
    }

    return sigma;
  /////////////////////////////////////////////////////////////////////////////
}
