#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

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
	double eps = 0.000000001;
	int hit_id = 0;
	double t = 0;
	Eigen::Vector3d n;
	if (!first_hit(ray, min_t, objects, hit_id, t, n))
		return false;
	if (num_recursive_calls < 7) {
		Ray mirror_ray = { ray.origin + t * ray.direction + eps * n, reflect(ray.direction, n) };
		if (raycolor(mirror_ray, eps, objects, lights, num_recursive_calls + 1, rgb))
			rgb = rgb.cwiseProduct(objects.at(hit_id)->material->km);
	}
	
	Eigen::Vector3d colour = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
	rgb += colour;
	
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
