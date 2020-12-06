#pragma once


#include <src/point/Point3d.h>
#include <src/vector/Vector3d.h>

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
  Ray(Point3d &origin, Vector3d &direction);

  [[nodiscard]] Point3d getPointOnParameter(float t) const;

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Point3d &point);
};
