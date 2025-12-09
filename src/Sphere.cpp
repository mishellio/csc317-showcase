#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	Eigen::Vector3d e_c = ray.origin - center;
	double a = ray.direction.dot(ray.direction);
	double b = 2.0*ray.direction.dot(e_c);
	double c = e_c.dot(e_c) - (radius*radius);
	double discriminant = (b*b) - 4.0 * a * c;

	if (discriminant < 0)
		return false;

	t = (-b + sqrt(discriminant)) / (2.0 * a);
	n = (ray.origin + t * ray.direction - center) / radius;
	if (discriminant == 0)
		return t >= min_t;

	double temp_t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (temp_t < t && temp_t >= min_t) {
		t = temp_t;
		n = (ray.origin + t * ray.direction - center) / radius;
	}
	return t >= min_t;
	////////////////////////////////////////////////////////////////////////////
}

