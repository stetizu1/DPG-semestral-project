#pragma once

#include <vector>

#include "src/light/Light.h"
#include "src/material/Material.h"
#include "src/color/Color.h"
#include "src/ray/Ray.h"
#include "src/helper-types/Intersection.h"

/**
 * Class to work with illumination
 */
class Illumination {
public:
  /**
   * Get direct phong illumination at ray-triangle intersection
   * @param lights - scene lights
   * @param material - material of the triangle
   * @param ray - intersected ray
   * @param intersection - intersection determined by parameter t and normal
   * @return color at the intersection
   */
  static Color getDirectPhongIllumination(const std::vector<Light> &lights, const Material &material, const Ray &ray, const Intersection &t, float heightFactor = 0.f);
};
