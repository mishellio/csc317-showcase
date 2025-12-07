#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

bool Triangle::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	Eigen::Vector3d a = std::get<0>(corners);
	Eigen::Vector3d b = std::get<1>(corners);
	Eigen::Vector3d c = std::get<2>(corners);
	Eigen::Matrix3d m_a;
	m_a <<
		a.x() - b.x(), a.x() - c.x(), ray.direction.x(),
		a.y() - b.y(), a.y() - c.y(), ray.direction.y(),
		a.z() - b.z(), a.z() - c.z(), ray.direction.z();
	double m_a_determinant = m_a.determinant();

	Eigen::Vector3d v_b;
	v_b << a.x() - ray.origin.x(), a.y() - ray.origin.y(), a.z() - ray.origin.z();

	Eigen::Matrix3d m_t;
	m_t = m_a;
	m_t.col(2) = v_b;
	double temp_t = m_t.determinant() / m_a_determinant;
	if (temp_t < min_t)
		return false;

	Eigen::Matrix3d m_beta;
	m_beta = m_a;
	m_beta.col(1) = v_b;
	double beta = m_beta.determinant() / m_a_determinant;
	if (beta <= 0 || beta >= 1)
		return false;

	Eigen::Matrix3d m_alpha;
	m_alpha = m_a;
	m_alpha.col(0) = v_b;
	double alpha = m_alpha.determinant() / m_a_determinant;
	if (alpha <= 0 || alpha >= 1 - beta)
		return false;

	t = temp_t;
	n = m_a.col(0).cross(m_a.col(1)).normalized();

	return true;
	////////////////////////////////////////////////////////////////////////////
}