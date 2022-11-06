#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
    I = -1;
    sqrD = std::numeric_limits<double>::infinity();
    // loop through all points
    for (int i = 0; i < points.rows(); ++i) {
        // calculate squared distance for each point (normalized)
        double squared_distance = (points.row(i) - query).squaredNorm();
        // if we found new smallest distance update index and distance value
        if (squared_distance < sqrD) {
            I = i;
            sqrD = squared_distance;
        }
    }
  ////////////////////////////////////////////////////////////////////////////
}
