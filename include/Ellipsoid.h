#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Ellipsoid.h"
#include "Object.h"
#include <Eigen/Core>

class Ellipsoid : public Object
{
public:
    Eigen::Vector3d center;
    double radius_x;
    double radius_y;
    double radius_z;
public:
    // Intersect sphere with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    bool intersect(
        const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const;
};

#endif
