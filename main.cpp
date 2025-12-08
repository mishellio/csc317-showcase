#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include <random>


int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  // Read a camera and scene description from given .json file
  read_json(
    argc<=1?"../data/creative.json":argv[1],
    camera,
    objects,
    lights);

  int width =  640;
  int height = 360;
  std::vector<unsigned char> rgb_image(3*width*height);
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> distrib(0.0, 1.0);
  // For each pixel (i,j)
  for(unsigned i=0; i<height; ++i) 
  {
    for(unsigned j=0; j<width; ++j)
    {
      // Set background color
      Eigen::Vector3d rgb(0,0,0);

      // Compute viewing ray
      int steps = 4;
      double interval = 1.0 / steps;
      double num_samples = steps * steps;
      for (int y = 0; y < steps; y++) {
          for (int x = 0; x < steps; x++) {
              Eigen::Vector3d rgb_temp(0, 0, 0);
              // Offset based on grid position + small random jitter
              double offset_x = (x + distrib(gen)) * interval;
              double offset_y = (y + distrib(gen)) * interval;

              double u = (j + offset_x);
              double v = (i + offset_y);

              Ray ray;
              viewing_ray(camera, v, u, width, height, ray);

              // Shoot ray and collect color
              raycolor(ray, 1.0, objects, lights, 0, rgb_temp);
              rgb += rgb_temp;
          }
      }
      rgb = rgb / num_samples;

      // Write double precision color into image
      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      rgb_image[0+3*(j+width*i)] = 255.0*clamp(rgb(0));
      rgb_image[1+3*(j+width*i)] = 255.0*clamp(rgb(1));
      rgb_image[2+3*(j+width*i)] = 255.0*clamp(rgb(2));

    }
  }

  write_ppm("rgb.ppm",rgb_image,width,height,3);
}
