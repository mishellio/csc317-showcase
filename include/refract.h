#ifndef REFRACT_H
#define REFRACT_H
#include <Eigen/Core>
// Reflect an incoming ray into an out going ray
//
// Inputs:
//   in  incoming _unit_ ray direction
//   n  surface _unit_ normal about which to reflect
// Returns outward _unit_ ray direction
bool refract(const Eigen::Vector3d& in, const Eigen::Vector3d& n, const double& ior, Eigen::Vector3d& d);
double schlick_approximation(const Eigen::Vector3d& in, const Eigen::Vector3d& n, const double& ior);
#endif 