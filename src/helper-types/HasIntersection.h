#pragma once

#include "src/vector/Vector3d.h"

class HasIntersection {
  struct intersection {
    float t = 0.f;
    Vector3d normal;
  };
  bool exists = true;
  intersection p;
  HasIntersection() = default;

public:
  /**
   * Create intersection structure marking intersection as non-existent
   */
  static HasIntersection doesNotIntersect() {
    auto noIntersection = HasIntersection();
    noIntersection.exists = false;
    return noIntersection;
  }

  /**
   * Create intersection with t and normal
   * @param t - parameter of intersection
   * @param normal - normal on the intersection
   */
  explicit HasIntersection(float t, const Vector3d &normal) : p{t, normal} {}

  /**
   * Returns true if
   * @return
   */
  [[nodiscard]] bool isExisting() const {
    return exists;
  }
  [[nodiscard]] float getT() const {
    return p.t;
  }

  [[nodiscard]] const Vector3d &getNormal() const {
    return p.normal;
  }
};

