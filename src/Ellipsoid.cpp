#include "Ellipsoid.h"
#include "Ray.h"
bool Ellipsoid::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	Eigen::Vector3d scale = { radius_x, radius_y, radius_z };
	Ray transform = ray;
	transform.direction = transform.direction.cwiseQuotient(scale);
	double radius = 1;

	Eigen::Vector3d e_c = transform.origin - center;
	e_c = e_c.cwiseQuotient(scale);
	double a = transform.direction.dot(transform.direction);
	double b = 2.0 * transform.direction.dot(e_c);
	double c = e_c.dot(e_c) - (radius * radius);
	double discriminant = (b * b) - 4.0 * a * c;

	if (discriminant < 0)
		return false;

	t = (-b + sqrt(discriminant)) / (2.0 * a);
	scale = scale.cwiseProduct(scale);
	if (discriminant == 0) {
		n = ((ray.origin + t * ray.direction - center).cwiseQuotient(scale)).normalized();
		return t >= min_t;
	}

	double temp_t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (temp_t < t && temp_t >= min_t) {
		t = temp_t;
	}
	if (t < min_t)
		return false;
	n = ((ray.origin + t * ray.direction - center).cwiseQuotient(scale)).normalized();
	return true;
	////////////////////////////////////////////////////////////////////////////
}

