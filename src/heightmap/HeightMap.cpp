#include "HeightMap.h"


HeightMap::HeightMap(unsigned height, const HeightMapReader &reader) : height(height) {
  auto imgHeight = reader.getImageHeight(), imgWidth = reader.getImageWidth();
  map = std::vector<std::vector<Cell>>(imgHeight - 1);
  for (auto row = 0; row < imgHeight - 1; row++) {
    map[row] = std::vector<Cell>(imgWidth - 1);
    for (auto col = 0; col < imgWidth - 1; col++) {
      float values[] = {
        reader.getIntensityAt(row, col),
        reader.getIntensityAt(row, col + 1),
        reader.getIntensityAt(row + 1, col),
        reader.getIntensityAt(row + 1, col + 1)
      };
      map[row][col] = {
        values[0], values[1], values[2], values[3],
        std::max(std::max(values[0], values[1]), std::max(values[2], values[3]))
      };
    }
  }
}

unsigned HeightMap::getXWidth() const {
  return map.size();
}

unsigned HeightMap::getZWidth() const {
  return map[0].size();
}

std::string HeightMap::to_string() const {
  auto H = std::to_string(height);
  std::string s = "heightMap(\r\n";
  for (auto x = 0; x < getXWidth(); x++) {
    s += "  ";
    for (auto z = 0; z < getZWidth(); z++) {
      auto at = map[x][z];
      s += "{"
        + std::to_string(at.topLeft).substr(0, 4) + ","
        + std::to_string(at.topRight).substr(0, 4) + ","
        + std::to_string(at.bottomLeft).substr(0, 4) + ","
        + std::to_string(at.bottomRight).substr(0, 4) + " --> "
        + std::to_string(at.maxHeight).substr(0, 4) + "} ";
    }
    s += "\r\n";
  }
  s += ") with height set to " + H;
  return s;
}
std::ostream &operator<<(std::ostream &out, const HeightMap &h) {
  out << h.to_string();
  return out;
}
