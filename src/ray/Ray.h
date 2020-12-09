#pragma once

#include "src/point/Point3d.h"
#include "src/vector/Vector3d.h"

/**
 * Type for ray with origin and direction
 */
class Ray {
  Point3d origin;
  Vector3d direction;

public:
  /**
   * Crate ray with given origin and direction
   * @param origin - origin of the ray
   * @param direction - direction where ray is heading
   */
  explicit Ray(const Point3d &origin, const Vector3d &direction);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Point3d &point);

  /**
   * Get point on parameter t
   * @param t - parameter
   * @return 3d point on parameter
   */
  [[nodiscard]] Point3d getPointOnParameter(float t) const;

  /**
   * Get ray origin
   * @return origin of the ray
   */
  [[nodiscard]] const Point3d &getOrigin() const;

  /**
   * Get ray direction
   * @return direction of the ray
   */
  [[nodiscard]] const Vector3d &getDirection() const;
};
