#pragma


#include <vector>
#include <src/heightmap-reader/HeightMapReader.h>
#include <src/point/Point3d.h>

/**
 * Class to store height map, that was read by HeightMapReader
 */
class HeightMap {
  struct Cell {
    float topLeft, topRight, bottomLeft, bottomRight;
    float maxHeight;
  };
  std::vector<std::vector<Cell>> map;
  unsigned height, width, depth;
  Point3d position;

public:
  /**
   * Create height map from height map reader with given parameters
   * @param reader - HeightMapReader that was used to read file with heightmap
   * @param width - width of the height map
   * @param height - height of the height map
   * @param depth - depth of the height map
   */
  HeightMap(const HeightMapReader &reader, unsigned width, unsigned height, unsigned depth);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const HeightMap &h);

   /**
    * Set coordinates of the heightmap
    * @param point3D - coordinates given by 3d point
    */
  void setPosition(Point3d &point3D);

  /**
   * Get coordinates of the heightmap
   * @return 3d point representing coordinates
   */
  [[nodiscard]] const Point3d &getPosition() const;

};
