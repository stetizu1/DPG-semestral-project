#pragma once

#include "Grid.h"
#include "src/helper-types/Intersection.h"
#include "src/point/Point3d.h"
#include "src/ray/Ray.h"

/**
 * Class expanding grid with intersection search operations
 */
class GridIntersection : public Grid {
  /**
   * Struct for storing transformation to be applied
   */
  struct Transformation {
    bool swapXZ;
    bool plusX;
    bool plusZ;
    Point2i first;
    Transformation(bool swapXz, bool plusX, bool plusZ, const Point2i &first);
  };

  /**
   * Finds intersection in given run
   * @param transformation - transformation to be applied to run
   * @param from - coordinate where the run starts (originally x)
   * @param to - coordinate where the run ends (originally x)
   * @param otherCoord other run coordinate (originally y)
   * @param initY - Y at the from point (when enters the grid)
   * @param stepY - step how Y is changed with change of the direction given by transformation
   * @param ray - original ray we are investigating
   * @param intersection - where found intersection is stored
   * @return true if intersection in run is found
   */
  [[nodiscard]] bool findIntersectionInRun(const Transformation &transformation, int from, int to, int otherCoord, float initY, float stepY, const Ray &ray, Intersection &intersection) const;

  /**
   * Find intersection between normalized ray and height field
   * @param transformation - transformation to be applied to run
   * @param from - point where ray traversal begins
   * @param initY - Y at the from point (when ray enters the grid)
   * @param stepY - step how Y is changed with change of the direction given by transformation
   * @param gridRay - ray projected to the grid
   * @param ray - original ray we are investigating
   * @param intersection - where found intersection is stored
   * @return true if intersection in run is found
   */
  [[nodiscard]] bool findBasicRayIntersection(const Transformation &transformation, const Point2d &from, float initY, float stepY, const Point2d &gridRay, const Ray &ray, Intersection &intersection) const;

  /**
   * Looks if given points form vertical or horizontal line. If so, finds if there is any intersection between the ray on the vertical / horizontal line
   * @param gridPointFrom - point where ray enters the height field
   * @param gridPointTo - point where ray leaves the height field
   * @param initY - Y at the gridPointFrom point (when ray enters the grid)
   * @param toY - Y at the gridPointTo point (when ray leaves the grid)
   * @param ray - original ray we are investigating
   * @param intersection - where found intersection is stored
   * @return 0 if line is not vertical/horizontal, -1 if it is, but intersection is not found, 1 if intersection is found
   */
  [[nodiscard]] int checkVerticalAndHorizontalIntersection(const Point2d &gridPointFrom, const Point2d &gridPointTo, float initY, float toY, const Ray &ray, Intersection &intersection) const;
protected:
  /**
   * Create grid from given map reader
   * @param reader - reader of the height map file
   * @param height - height of the whole height map
   * @param cellW - width of the cell
   * @param cellD - depth of the cell
   * @param position - position of the grid (map)
   */
  GridIntersection(const MapReader &reader, float height, float cellW, float cellD, const Point3d &position);

  /**
   * Find intersection between ray and height map
   * @param from - point where ray enters the height map bounding box
   * @param to - point where ray leaves the height map bounding box
   * @param ray - ray we are investigating
   * @param intersection - where found intersection is stored
   * @return true if intersection exists
   */
  [[nodiscard]] bool findRayIntersection(const Point3d &from, const Point3d &to, const Ray &ray, Intersection &intersection) const;
};
