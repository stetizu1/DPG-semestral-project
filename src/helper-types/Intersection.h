#pragma once

#include "src/vector/Vector3d.h"

/**
 * Class to store intersection values - parameter t and normal of the intersection
 */
class Intersection {
    float t;
    Vector3d normal;
public:
  /**
   * Create empty intersection with 0 values
   */
  Intersection() : t(0.f), normal() {}
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

