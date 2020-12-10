#pragma once

#include "src/color/Color.h"

class Material {
  Color color;
  float kd;
  float ks;
  float shine;

public:
  /**
   * Create material with given color and properties (color, kd, ks, shine)
   * @param color - color of the material
   * @param kd - diffuse coefficient of the material
   * @param ks - specular coefficient of the material
   * @param shine - cosine power for highlights
   */
  Material(const Color &color, float kd, float ks = 0, float shine = 0);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Material &m);

  /**
   * Get color of the material
   * @return rgb color
   */
  [[nodiscard]] const Color &getColor() const;

  /**
   * Get diffuse coefficient of the material
   * @return diffuse coefficient
   */
  [[nodiscard]] float getKd() const;

  /**
   * Get specular coefficient of the material
   * @return specular coefficient
   */
  [[nodiscard]] float getKs() const;

  /**
   * Get shine (cosine power of highlights) of the material
   * @return shine
   */
  [[nodiscard]] float getShine() const;
};
