#include "PointLight.h"
#include <random>
#include <Eigen/Geometry>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
	d = p - q;
	max_t = 1;
  ////////////////////////////////////////////////////////////////////////////
}

Eigen::MatrixXd PointLight::sample() const
{
    int steps = 8;
    int num_samples = steps * steps;

    Eigen::MatrixXd points(num_samples, 3);
    points.setZero();
    Eigen::Vector3d origin = { 0, 0, 0 };
    Eigen::Vector3d d_n = (origin - p).normalized();
    Eigen::Vector3d helper = { 0, 1, 0 };
    if (std::abs(d_n.y()) > 0.99) helper = { 0, 0, 1 };

    Eigen::Vector3d right_n = (helper.cross(d_n)).normalized();
    Eigen::Vector3d up_n = (d_n.cross(right_n)).normalized();
    Eigen::Vector3d right = right_n * width;
    Eigen::Vector3d up = up_n * height;

    Eigen::Vector3d corner = p - (right * 0.5) - (up * 0.5);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(0.0, 1.0);

    double interval = 1.0 / steps;
    int count = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < steps; j++) {
            double r1 = distrib(gen);
            double r2 = distrib(gen);

            double u = (j + r1) * interval;
            double v = (i + r2) * interval;
            points.row(count) = corner + (right * u) + (up * v);
            count++;
        }
    }

    return points;

}
