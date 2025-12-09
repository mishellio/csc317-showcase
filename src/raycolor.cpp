#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "refract.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	rgb.setZero();
	double eps = 0.000000001;
	int hit_id = 0;
	double t = 0;
	Eigen::Vector3d n;
	if (!first_hit(ray, min_t, objects, hit_id, t, n))
		return false;
	if (num_recursive_calls < 4) {
		double schlick = 1;
		Eigen::Vector3d refracted_direction;
		if (!objects.at(hit_id)->material->kt.isZero()) {
			if (refract(ray.direction, n, objects.at(hit_id)->material->ior, refracted_direction)) {
				Eigen::Vector3d rgb_refract = { 0,0,0 };
				Ray refract_ray = { ray.origin + t * ray.direction + eps * refracted_direction, refracted_direction };
				if (raycolor(refract_ray, eps, objects, lights, num_recursive_calls + 1, rgb_refract)) {
					schlick = schlick_approximation(ray.direction.normalized(), n, objects.at(hit_id)->material->ior);
					rgb += rgb_refract.cwiseProduct(objects.at(hit_id)->material->kt) * (1 - schlick);
				}
				else {
					schlick = 1;
				}
			}
		}
		Eigen::Vector3d reflected_direction = reflect(ray.direction, n);
		Ray mirror_ray = { ray.origin + t * ray.direction + eps * reflected_direction, reflect(ray.direction, n) };
		Eigen::Vector3d rgb_mirror(0, 0, 0);
		if (raycolor(mirror_ray, eps, objects, lights, num_recursive_calls + 1, rgb_mirror))
			rgb += rgb_mirror.cwiseProduct(objects.at(hit_id)->material->km) * schlick;


	}

		Eigen::Vector3d colour = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
		rgb += colour;

	
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
