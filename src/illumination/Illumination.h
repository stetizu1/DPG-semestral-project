#pragma once

#include "src/material/Material.h"
#include "src/color/Color.h"
#include "src/triangle/Triangle.h"
#include "src/context/Context.h"

class Illumination {

public:
  /**
   * Get direct phong illumination at ray-triangle intersection
   * @param context - scene context
   * @param material - material of the triangle
   * @param triangle - intersected triangle
   * @param ray - intersected ray
   * @param t - parameter of intersection
   * @return color at the intersection
   */
  static Color getDirectPhongIllumination(const Context &context, const Material &material, const Triangle &triangle, const Ray &ray, float t);
};
