#pragma once

#include <string>
#include <src/point/Point3d.h>
#include "Vector3d.h"

class Vector4d {
  float x, y, z, w;

public:
  /**
   * Create 4D vector (0,0,0,1)
   */
  explicit Vector4d();

  /**
   * Create vector with provided x, y, z and possibly w
   * @param x - length in x axis
   * @param y - length in y axis
   * @param z - length in z axis
   * @param w - factor for normalization
   */
  explicit Vector4d(float x, float y, float z, float w = 1);

  /**
   * Create vector from provided array of length 4.
   * @param arr - array containing [x, y, z, w] in this order
   */
  explicit Vector4d(float arr[4]);

  Vector4d operator+(const Vector4d &other) const;
  Vector4d operator-(const Vector4d &other) const;

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Vector4d &vector);

  /**
   * Returns 3d point by dividing by w
   */
  [[nodiscard]] Point3d divideByW() const;

  /**
   * Returns 3d vector by ignoring w
   */
  [[nodiscard]] Vector3d ignoreW() const;

   /**
   * Get x direction of 4d vector
   * @return x
   */
  [[nodiscard]] float getX() const;

  /**
   * Get y direction of 4d vector
   * @return y
   */
  [[nodiscard]] float getY() const;

  /**
   * Get z direction of 4d vector
   * @return z
   */
  [[nodiscard]] float getZ() const;

  /**
   * Get factor w
   * @return w
   */
  [[nodiscard]] float getW() const;

  /**
   * Get i-th parameter of the vector, for example y for i = 1.
   * @param i number of parameter in list [x, y, z, w]
   * @return x, y, z or w
   */
  [[nodiscard]] float get(int i) const;
};
