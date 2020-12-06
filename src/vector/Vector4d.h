#pragma once

#include <string>
#include "Vector3d.h"

class Vector4d {
  float x, y, z, w;

public:
  explicit Vector4d(float x = 0, float y = 0, float z = 0, float w = 1);
  explicit Vector4d(float arr[4]);

  Vector4d operator+(const Vector4d &other) const;
  Vector4d operator-(const Vector4d &other) const;

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Vector4d &vector);

  /**
   * Returns 3d vector by dividing by w
   */
  [[nodiscard]] Vector3d divideByW() const;
  /**
   * Returns 3d vector by ignoring w
   */
  [[nodiscard]] Vector3d ignoreW() const;
  [[nodiscard]] float getX() const;
  [[nodiscard]] float getY() const;
  [[nodiscard]] float getZ() const;
  [[nodiscard]] float getW() const;
  [[nodiscard]] float get(int i) const;
};
