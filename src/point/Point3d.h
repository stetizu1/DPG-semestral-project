#pragma once

#include <ostream>
#include <string>

#include "src/vector/Vector3d.h"

/**
 * Type for 3D point
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
  friend Vector3d operator-(Vector3d &vector, const Point3d &point);
  Point3d operator-=(const Vector3d &vector);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Point3d &point);

  /**
   * Get x coordinate of the point
   * @return x coordinate
   */
  [[nodiscard]] float getX() const;

  /**
   * Get y coordinate of the point
   * @return y coordinate
   */
  [[nodiscard]] float getY() const;

  /**
   * Get z coordinate of the point
   * @return z coordinate
   */
  [[nodiscard]] float getZ() const;

  /**
   * Get i-th coordinate of the point, for example y for i = 1.
   * @param i number of parameter in list [x, y, z]
   * @return x, y or z
   */
  [[nodiscard]] float get(unsigned i) const;

  /**
   * Get minimal coordinates in x, y and z separately from this and other point
   * @param other - other point
   * @return minimal coordinates in x, y and z
   */
  [[nodiscard]] Point3d minimalCoords(Point3d &other) const;

  /**
   * Get maximal coordinates in x, y and z separately from this and other point
   * @param other - other point
   * @return maximal coordinates in x, y and z
   */
  [[nodiscard]] Point3d maximalCoords(Point3d &other) const;

  /**
   * Get vector between this and other point
   * @return 3d vector between this and other point
   */
  [[nodiscard]] Vector3d getVectorBetween(const Point3d &other) const;

  /**
   * Get normalized vector between this and other point
   * @return normalized 3d vector between this and other point
   */
  [[nodiscard]] Vector3d getNormalizedVectorBetween(const Point3d &other) const;
};
