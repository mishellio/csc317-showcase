#include "first_hit.h"

bool first_hit(
	const Ray& ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> >& objects,
	int& hit_id,
	double& t,
	Eigen::Vector3d& n)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	bool hit = false;
	t = -1; // temp state to be overwritten if there is intersecting object (t should never be negative otherwise)
	for (int id = 0; id < objects.size(); id++) {
		double temp_t;
		Eigen::Vector3d temp_n;
		if (objects.at(id)->intersect(ray, min_t, temp_t, temp_n)) {
			if (temp_t < t || t == -1) {
				t = temp_t;
				n = temp_n;
				hit_id = id;
				hit = true;
			}
		}
	}
	return hit;
	////////////////////////////////////////////////////////////////////////////
}

