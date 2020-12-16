#include "Grid.h"

Grid::Grid(const MapReader &reader, float height, float cellW, float cellD, const Point3d &position) : map(std::vector<std::vector<Cell>>(reader.getImageHeight() - 1)), cellWidth(cellW), cellDepth(cellD), position(position) {
  auto imgHeight = reader.getImageHeight();
  auto imgWidth = reader.getImageWidth();
  map = std::vector<std::vector<Cell>>(imgHeight - 1);
  for (auto row = 0; row < imgHeight - 1; row++) {
    map[row] = std::vector<Cell>(imgWidth - 1);
    for (auto col = 0; col < imgWidth - 1; col++) {
      auto h = height;
      auto y = position.getY();
      float values[] = {
        reader.getIntensityAt(row, col) * h + y,
        reader.getIntensityAt(row, col + 1) * h + y,
        reader.getIntensityAt(row + 1, col) * h + y,
        reader.getIntensityAt(row + 1, col + 1) * h + y
      };

      auto xPos = position.getX() + cellWidth * col;
      auto zPos = position.getZ() + cellDepth * row;
      map[row][col] = Cell(values[0], values[1], values[2], values[3], xPos, zPos, cellWidth, cellDepth);
    }
  }
}

unsigned Grid::getGridDepth() const {
  return map.size();
}

unsigned Grid::getGridWidth() const {
  return map[0].size();
}

Point2d Grid::getGridPoint(const Point3d &pos) const {
  auto moved = pos - position;
  auto x = moved.getX() / cellWidth;
  auto z = moved.getZ() / cellDepth;
  return Point2d(x, z);
}

Point2i Grid::getGridCoordinates(const Point3d &pos) const {
  auto base = getGridPoint(pos);
  auto x = std::min(int(base.getX()), int(getGridWidth()));
  auto y = std::min(int(base.getZ()), int(getGridDepth()));
  return Point2i(x, y);
}
