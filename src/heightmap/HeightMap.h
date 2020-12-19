#pragma once

#include <vector>

#include "GridIntersection.h"
#include "cell/Cell.h"
#include "heightmap-reader/MapReader.h"
#include "src/material/Material.h"
#include "src/ray/Ray.h"
#include "src/helper-types/Intersection.h"
#include "src/vector/Vector3d.h"
#include "src/point/Point3d.h"
#include "src/point/Point2d.h"
#include "src/point/Point2i.h"

/**
 * Class to store height map, that was read by HeightMapReader
 *
 * Provides height map data and functions for finding ray-heightmap intersections
 */
class HeightMap : public GridIntersection {
  const float height, width, depth;
  const Material material;
  Point3d aabbMin, aabbMax;

  /**
   * Find local parameters t low and t high in dimension given by d (0-x, 1-y, 2-z)
   * Rewrite tLow, tHigh if result is higher / lower
   * @param d - dimension (0-x, 1-y, 2-z)
   * @param minToOrigin - vector from AABB-min to ray origin
   * @param maxToOrigin - vector from AABB-max to ray origin
   * @param direction - direction of the ray
   * @param tLow - current found tLow
   * @param tHigh - current found tHigh
   * @return true if intersection exists in given dimension
   */
  [[nodiscard]] static bool findIntersectionInAxis(unsigned d, const Vector3d &minToOrigin, const Vector3d &maxToOrigin, const Vector3d &direction, float &tLow, float &tHigh);

  /**
   * Find intersection in y axis, returns if there is any
   * @param minToOrigin - vector from AABB-min to ray origin
   * @param maxToOrigin - vector from AABB-max to ray origin
   * @param direction - direction of the ray
   * @param tLow - current found tLow
   * @param tHigh - current found tHigh
   * @return true if intersection exist in y dimension
   */
  static bool hasHeightIntersection(const Vector3d &minToOrigin, const Vector3d &maxToOrigin, const Vector3d &direction, float tLow, float tHigh);

  /**
   * Find t low and t high between AABB of the height map and ray
   * @param ray - investigated ray
   * @param tLow - variable where tLow is stored
   * @param tHigh - variable where tHigh is stored
   * @return true if intersection exists
   */
  [[nodiscard]] bool hasIntersectionWithBoundingBox(const Ray &ray, float &tLow, float &tHigh) const;

public:
  /**
   * Create height map from height map reader with given parameters
   * @param reader - HeightMapReader that was used to read file with heightmap
   * @param position - position of the height map
   * @param size - vector storing width, depth and height of the height map
   * @param width - width of the height map
   * @param height - height of the height map
   * @param depth - depth of the height map
   * @param material - material of the heightmap
   */
  explicit HeightMap(const MapReader &reader, const Point3d &position, const Vector3d &size, const Material &material);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const HeightMap &h);

  /**
   * Get coordinates of the heightmap
   * @return 3d point representing coordinates
   */
  [[nodiscard]] const Point3d &getPosition() const;

  /**
   * Get material of the heightmap
   * @return material of the height map
   */
  [[nodiscard]] const Material &getMaterial() const;

  /**
   * Get height fraction of the height map
   * @return height fraction (ratio how high is the point against max heightmap height)
   */
  [[nodiscard]] float getHeightFraction(float y) const;

  /**
   * Find intersection between ray and this height map
   * @param ray - investigated ray
   * @param intersection - intersection, stays unchanged if none found
   * @return true if intersection is found
   */
  [[nodiscard]] bool findIntersection(const Ray &ray, Intersection &intersection) const;
};
