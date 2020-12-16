#pragma once

#include <vector>
#include <utility>
#include <src/heightmap/heightmap-reader/MapReader.h>

#include "cell/Cell.h"
#include "src/point/Point2d.h"
#include "src/point/Point2i.h"

/**
 * Class for grid underlying the height field
 */
class Grid {
protected:
  std::vector<std::vector<Cell>> map;
  const float cellWidth, cellDepth;
  const Point3d position;

  /**
   * Create grid from given map reader
   * @param reader - reader of the height map file
   * @param height - height of the whole height map
   * @param cellW - width of the cell
   * @param cellD - depth of the cell
   * @param position - position of the grid (map)
   */
  Grid(const MapReader &reader, float height, float cellW, float cellD, const Point3d &position);

public:
  /**
   * Get depth of the map - number of rows
   * @return depth of map grid
   */
  [[nodiscard]] unsigned getGridDepth() const;

  /**
   * Get width of the map - number of columns
   * @return width of the map grid
   */
  [[nodiscard]] unsigned getGridWidth() const;

  /**
   * Get coordinates in the map grid (rows and columns)
   * @return 2d coordinate point
   */
  [[nodiscard]] Point2d getGridPoint(const Point3d &pos) const;

  /**
   * Get map coordinates of the given point (rows and columns indices)
   * @return 2d coordinate for height map
   */
  [[nodiscard]] Point2i getGridCoordinates(const Point3d &pos) const;
};

