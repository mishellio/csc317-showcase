#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	if (normal.dot(ray.direction) == 0)
		return false;
	t = (-normal.dot(ray.origin - point)) / (normal.dot(ray.direction));
	n = normal.normalized();
	return t >= min_t;
	////////////////////////////////////////////////////////////////////////////
}

