#pragma


#include <vector>
#include <src/heightmap-reader/HeightMapReader.h>

class HeightMap {
  struct Cell {
    float topLeft, topRight, bottomLeft, bottomRight;
    float maxHeight;
  };
  unsigned height;
  std::vector<std::vector<Cell>> map;

public:
  HeightMap(unsigned height, const HeightMapReader &reader);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const HeightMap &h);

  [[nodiscard]] unsigned getXWidth() const;

  [[nodiscard]] unsigned getZWidth() const;

};
