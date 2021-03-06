#pragma once

#include "src/color/Color.h"

/**
 * Color changing types
 */
enum ColorChanging {
  NONE,
  LAVA,
  ICE,
  FIELDS
};

/**
 * Type for storing the material values
 */
class Material {
  Color color;
  float kd;
  float ks;
  float shine;
  ColorChanging changing = ColorChanging::NONE;

public:
  /**
   * Create material with given color and properties (color, kd, ks, shine)
   * @param color - color of the material
   * @param kd - diffuse coefficient of the material
   * @param ks - specular coefficient of the material
   * @param shine - cosine power for highlights
   */
  explicit Material(const Color &color, float kd, float ks = 0, float shine = 0);

  /**
   * Create material with varying color due to height
   * @param c - type of changing color
   */
   explicit Material(ColorChanging c = ColorChanging::LAVA);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Material &m);

  /**
   * Get color of the material
   * @return rgb color
   */
  [[nodiscard]] const Color &getColor() const;

  /**
   * Get color due to height
   * @param heightFactor - height of the sample
   * @return rgb color
   */
  [[nodiscard]] Color getColor(float heightFactor) const ;

  /**
   * True if color is changing due to height
   * @return true if color depends on height
   */
  [[nodiscard]] bool isChangeColor() const;

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
