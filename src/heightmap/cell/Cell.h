#pragma once

#include <vector>
#include "src/helper-types/Intersection.h"
#include "src/triangle/Triangle.h"

/**
 * Type for one cell of the height map
 *
 * Provide operation for finding intersection with cell triangles
 */
class Cell {
  float maxHeight = 0.f;
  std::vector<Triangle> triangles;

public:
  /**
   * Create empty cell
   */
  Cell() = default;

  /**
   * Create cell with height samples
   * @param topLeft - y coordinate in top left corner
   * @param topRight - y coordinate in top right corner
   * @param bottomLeft - y coordinate in bottom left corner
   * @param bottomRight - y coordinate in bottom right corner
   * @param xPos - x coordinate of the cell top left corner
   * @param zPos - z coordinate of the cell top left corner
   * @param width - width of the cell (x)
   * @param depth - depth of the cell (z)
   */
  Cell(float topLeft, float topRight, float bottomLeft, float bottomRight, float xPos, float zPos, float width, float depth);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Cell &cell);

  /**
   * Find if there is an intersection between ray and the cell and store it if there is
   * @param ray - investigated ray
   * @param intersection - value where we store intersection if any is found
   * @param minHeight - minimal ray height in the bounding box
   * @return true if intersection is found
   */
  bool findIntersection(const Ray &ray, Intersection &intersection, float minHeight = -std::numeric_limits<float>::infinity()) const;
};