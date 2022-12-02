#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

# define PI           3.14159265358979323846  /* pi */

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  /*
   * Reference: Textbook section 15.5.3 - Cardinal Cubics
   */
    if (keyframes.empty()) {
        return Eigen::Vector3d::Zero();
    }
    t = std::fmod(t, keyframes.back().first);

    //Find index i for query time t. 
    int i = 0;
    for (i = 0; i < keyframes.size() - 1; i++) {
        if (t <= keyframes[i + 1].first && t > keyframes[i].first) {
            break;
        }
    }
    // Define point and time variables
    Eigen::Vector3d P0, P1, P2, P3;
    double t0, t1, t2, t3;                             
    double tension = 0.0;

    // Use Cosine interpolation for First and Last Point
    if (i == 0 || i == keyframes.size() - 2) {
        P0 = keyframes[i].second;
        P1 = keyframes[i + 1].second;
        t0 = keyframes[i].first;
        t1 = keyframes[i + 1].first;

        double u = (t - t0) / (t1 - t0);
        double mu = (1 - cos(u * PI)) / 2;
        return P0 * (1 - mu) + P1* mu;
    }

    // Use Catmull-rom for middle points
    // Source: https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline
    P0 = keyframes[i - 1].second;
    P1 = keyframes[i].second;
    P2 = keyframes[i + 1].second;
    P3 = keyframes[i + 2].second;

    t0 = keyframes[i - 1].first;
    t1 = keyframes[i].first;
    t2 = keyframes[i + 1].first;
    t3 = keyframes[i + 2].first;

    // Calculate unit parameter in [0, 1]
    double unit = (t - t1) / (t2 - t1);
    Eigen::RowVector4d u = Eigen::RowVector4d(1, unit, pow(unit, 2), pow(unit, 3));

    // Calculate derivatives/tangents at P1 and P2
    Eigen::Vector3d v1 = (P2 - P0) / (t2 - t0);
    Eigen::Vector3d v2 = (P3 - P1) / (t3 - t1);
    
    // Constraint matrix
    Eigen::Matrix4d C;
    C <<
        1, 1 - (t2 - t0),   1,              1,
        1, 0,               0,              0,
        1, 1,               1,              1,
        1, (t3 - t1),       2 * (t3 - t1),  3 * (t3 - t1);
    
    // Cardinal matrix
    Eigen::Matrix4d B = C.inverse();
    
    // Matrix for control points
    Eigen::Matrix<double, 4, 3> p;
    p.row(0) = P0;
    p.row(1) = P1;
    p.row(2) = P2;
    p.row(3) = P3;

    return u * B * p; // interpolation
  /////////////////////////////////////////////////////////////////////////////
}
