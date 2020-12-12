#pragma once

#include "src/vector/Vector3d.h"

class Intersection {
    float t = 0.f;
    Vector3d normal;
public:
  Intersection() : t(0), normal(0, 0, 0) {}
  /**
   * Create intersection with t and normal
   * @param t - parameter of intersection
   * @param normal - normal on the intersection
   */
  explicit Intersection(float t, const Vector3d &normal) : t(t), normal(normal) {}

  [[nodiscard]] float getT() const {
    return t;
  }

  [[nodiscard]] const Vector3d &getNormal() const {
    return normal;
  }
};

