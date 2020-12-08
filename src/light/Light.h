#pragma once

#include "src/color/Color.h"
#include "src/point/Point3d.h"

/**
 * Type for storing point light. Stores color and position as 3D point.
 */
class Light {
  Point3d position;
  Color colorIntensity;

public:
  /**
   * Create light on given position with given color intensity or white if none given
   * @param position - light position
   * @param colorIntensity - intensity of rgb colors
   */
  explicit Light(const Point3d &position, const Color &colorIntensity = Color());

public:
  /**
   * Get color intensities of light (rgb color)
   * @return rgb color of light
   */
  [[nodiscard]] const Color &getColorIntensity() const;

  /**
   * Get position of the light
   * @return 3d point, where the light is located
   */
  [[nodiscard]] const Point3d &getPosition() const;
};
