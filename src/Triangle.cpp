#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

bool Triangle::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	//referenced from: https://scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html
	double eps = 0.000000001;
	const Eigen::Vector3d& a = std::get<0>(corners);
	const Eigen::Vector3d& b = std::get<1>(corners);
	const Eigen::Vector3d& c = std::get<2>(corners);
	Eigen::Vector3d e1 = b - a;
	Eigen::Vector3d e2 = c - a;
	Eigen::Vector3d pvec = ray.direction.cross(e2);
	double det = e1.dot(pvec);

	if (abs(det) < eps)
		return false;

	double inv_det = 1 / det;
	Eigen::Vector3d tvec = ray.origin - a;
	double u = tvec.dot(pvec) * inv_det;
	if (u < 0 || u > 1) return false;

	Eigen::Vector3d qvec = tvec.cross(e1);
	double v = ray.direction.dot(qvec) * inv_det;
	if (v < 0 || u + v > 1) return false;

	double temp_t = e2.dot(qvec) * inv_det;
	if (temp_t < min_t)
		return false;
	t = temp_t;
	n = e1.cross(e2).normalized();

	return true;

	//Eigen::Matrix3d m_a;
	//m_a <<
	//	a.x() - b.x(), a.x() - c.x(), ray.direction.x(),
	//	a.y() - b.y(), a.y() - c.y(), ray.direction.y(),
	//	a.z() - b.z(), a.z() - c.z(), ray.direction.z();
	//double m_a_determinant = m_a.determinant();

	//Eigen::Vector3d v_b;
	//v_b << a.x() - ray.origin.x(), a.y() - ray.origin.y(), a.z() - ray.origin.z();

	//Eigen::Matrix3d m_t;
	//m_t = m_a;
	//m_t.col(2) = v_b;
	//double temp_t = m_t.determinant() / m_a_determinant;
	//if (temp_t < min_t)
	//	return false;

	//Eigen::Matrix3d m_beta;
	//m_beta = m_a;
	//m_beta.col(1) = v_b;
	//double beta = m_beta.determinant() / m_a_determinant;
	//if (beta <= 0 || beta >= 1)
	//	return false;

	//Eigen::Matrix3d m_alpha;
	//m_alpha = m_a;
	//m_alpha.col(0) = v_b;
	//double alpha = m_alpha.determinant() / m_a_determinant;
	//if (alpha <= 0 || alpha >= 1 - beta)
	//	return false;

	//t = temp_t;
	//n = m_a.col(0).cross(m_a.col(1)).normalized();

	//return true;
	////////////////////////////////////////////////////////////////////////////
}