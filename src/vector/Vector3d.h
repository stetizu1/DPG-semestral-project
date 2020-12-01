#pragma once

#include <ostream>
#include <string>

class Vector3d {
  float x, y, z;

public:
  Vector3d();
  /**
   * Create vector providing x, y, z
   * @param x - distance in x axis
   * @param y - distance in y axis
   * @param z - distance in z axis
   */
  Vector3d(float x, float y, float z);

  Vector3d operator+(const Vector3d &other) const;
  Vector3d operator+=(const Vector3d &other);

  Vector3d operator-(const Vector3d &other) const;
  Vector3d operator-=(const Vector3d &other);

  Vector3d operator*(float k) const;
  friend Vector3d operator*(float k, const Vector3d &point);
  Vector3d operator*=(float k);

  Vector3d operator/(float k) const;
  Vector3d operator/=(float k);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Vector3d &point);

  friend inline Vector3d operator-(const Vector3d &vector);

  // getters
  [[nodiscard]] float getX() const;
  [[nodiscard]] float getY() const;
  [[nodiscard]] float getZ() const;

  /**
   * Compute length of the vector.
   * @return length of the vector
   */
  [[nodiscard]] float length() const;

  /**
   * Compute dot product between this vector and the other and returns it.
   * @param other - vector to compute dot product with
   * @return dot product of this and the other vector
   */
  [[nodiscard]] float dotProduct(const Vector3d &other) const;

  /**
   * Compute cross product between this vector and the other and returns it.
   * @param other - vector to compute cross product with
   * @return cross product of this and the other vector
   */
  [[nodiscard]] Vector3d crossProduct(const Vector3d &other) const;

  /**
   * Compute normalized vector for this vector.
   * @return normalized version of this
   */
  [[nodiscard]] Vector3d normalized() const;
};
