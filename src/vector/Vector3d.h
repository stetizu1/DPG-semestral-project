#pragma once

#include <ostream>
#include <string>

/**
 * Type for 3D vector
 *
 * Provides basic meaningful operation (+, -, *, /) for vector
 * Provides vector-specific operations as getting length, normalization, dot product and cross product between vectors
 */
class Vector3d {
  float x, y, z;

public:
  /**
   * Create vector (0, 0, 0)
   */
  explicit Vector3d();

  /**
   * Create vector with provided x, y, z
   * @param x - length in x axis
   * @param y - length in y axis
   * @param z - length in z axis
   */
  explicit Vector3d(float x, float y, float z);

  Vector3d operator+(const Vector3d &other) const;
  Vector3d operator+=(const Vector3d &other);

  Vector3d operator-(const Vector3d &other) const;
  Vector3d operator-=(const Vector3d &other);

  Vector3d operator*(float k) const;
  friend Vector3d operator*(float k, const Vector3d &vector);
  Vector3d operator*=(float k);

  Vector3d operator/(float k) const;
  Vector3d operator/=(float k);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Vector3d &vector);

  friend Vector3d operator-(const Vector3d &vector);

  /**
   * Get x direction of vector
   * @return x
   */
  [[nodiscard]] float getX() const;

  /**
   * Get y direction of vector
   * @return y
   */
  [[nodiscard]] float getY() const;

  /**
   * Get z direction of vector
   * @return z
   */
  [[nodiscard]] float getZ() const;

  /**
   * Get i-th parameter of the vector, for example y for i = 1.
   * @param i number of parameter in list [x, y, z]
   * @return x, y or z
   */
  [[nodiscard]] float get(unsigned i) const;

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
