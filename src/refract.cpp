#include <Eigen/Core>

bool refract(const Eigen::Vector3d& in, const Eigen::Vector3d& n, const double& ior, Eigen::Vector3d& d)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	double cos_l = (in.normalized()).dot(n);
	double ratio;
	Eigen::Vector3d normal = n;
	if (cos_l < 0) { //is entering material
		ratio = 1.0 / ior;
		cos_l = -cos_l;
	}
	else { //is exiting material
		ratio = ior;
		normal = -n; // to point towards incoming ray
	}

	double k = 1 - (ratio * ratio) * (1 - cos_l * cos_l);
	if (k < 0) {
		return false;
	}

	d = (ratio * (in.normalized())) + (cos_l * ratio - sqrt(k)) * normal;
	d *= in.norm();
	return true;
	////////////////////////////////////////////////////////////////////////////
}

	double schlick_approximation(const Eigen::Vector3d& in, const Eigen::Vector3d& n, const double& ior) {
		double cos_l = in.dot(n);
		double r0 = (1 - ior) / (1 + ior);
		r0 = r0 * r0;
		if (cos_l < 0)
			cos_l = -cos_l;
		else {
			double sin_l_2 = 1 - cos_l * cos_l;
			double sin_t_2 = ior * ior * sin_l_2;
			if (sin_t_2 > 1)
				return 1;
			cos_l = sqrt(1 - sin_t_2);
		}

		return r0 + (1 - r0) * (1 - cos_l) * (1 - cos_l) * (1 - cos_l) * (1 - cos_l) * (1 - cos_l);
	}