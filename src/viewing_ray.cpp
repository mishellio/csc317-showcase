#include "viewing_ray.h"

void viewing_ray(
	const Camera& camera,
	const double i,
	const double j,
	const int width,
	const int height,
	Ray& ray)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	ray.origin = camera.e;
	ray.direction = ((camera.width / width) * (j + 0.5) - (camera.width / 2)) * camera.u +
		((camera.height / height) * (i + 0.5) - (camera.height / 2)) * -camera.v -
		camera.d * camera.w;
	////////////////////////////////////////////////////////////////////////////
}

