#pragma once

#include <ostream>
#include <string>

#include "src/vector/Vector3d.h"

/**
 * Type of 3D point
 *
 * Provides basic meaningful operation (+, -, *, /) for point and between point and vector (moving point on vector)
 */
class Point3d {
  float x, y, z;

public:
  explicit Point3d();
  /**
   * Create point with provided x, y, z coordinates.
   * @param x - x coordinate
   * @param y - y coordinate
   * @param z - z coordinate
   */
  explicit Point3d(float x, float y, float z);

  Point3d operator+(const Point3d &other) const;
  Point3d operator+=(const Point3d &other);

  Point3d operator-(const Point3d &other) const;
  Point3d operator-=(const Point3d &other);

  Point3d operator*(float k) const;
  friend Point3d operator*(float k, const Point3d &point);
  Point3d operator*=(float k);

  Point3d operator/(float k) const;
  Point3d operator/=(float k);

  Point3d operator+(const Vector3d &vector) const;
  friend Point3d operator+(Vector3d &vector, const Point3d &point);
  Point3d operator+=(const Vector3d &vector);

  Point3d operator-(const Vector3d &vector) const;
  friend Point3d operator-(Vector3d &vector, const Point3d &point);
  Point3d operator-=(const Vector3d &vector);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Point3d &point);
};
