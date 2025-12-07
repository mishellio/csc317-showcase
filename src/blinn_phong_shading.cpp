#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double eps = 0.000000001;
	double ia = 0.1;
	Eigen::Vector3d L = { 0, 0, 0 };
	Eigen::Vector3d p = ray.origin + t * ray.direction;
	std::shared_ptr<Object> object = objects.at(hit_id);
	for (int i = 0; i < lights.size(); i++) {
		std::shared_ptr<Light> light = lights.at(i);
		double max_t = 0;

		Ray shadow_ray;
		shadow_ray.origin = p + eps * n;
		light->direction(shadow_ray.origin, shadow_ray.direction, max_t);
		

		int temp_hit_id;
		double temp_t;
		Eigen::Vector3d temp_n;
		if (first_hit(shadow_ray, 0, objects, temp_hit_id, temp_t, temp_n)) {
			if (temp_t <= max_t)
				continue;
		}

		Ray v = { p, -ray.direction.normalized() };
		Ray l = { p, shadow_ray.direction.normalized() };
		Ray h = { p, (l.direction + v.direction).normalized() };

		Eigen::Vector3d light_colour = light->I;

		L += light_colour.cwiseProduct(object->material->ks) * pow(std::max(0., n.dot(h.direction)), object->material->phong_exponent);
		L += light_colour.cwiseProduct(object->material->kd) * std::max(0., n.dot(l.direction));
		
	}
	L += object->material->ka * ia;
  return L;
  ////////////////////////////////////////////////////////////////////////////
}
