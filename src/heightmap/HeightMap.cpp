#include "HeightMap.h"

bool HeightMap::findIntersectionInAxis(unsigned d, const Vector3d &minToOrigin, const Vector3d &maxToOrigin, Vector3d &direction, float &tLow, float &tHigh) {
  float tDimLow = minToOrigin.get(d) / direction.get(d);
  float tDimHigh = maxToOrigin.get(d) / direction.get(d);

  if (tDimHigh < tDimLow) std::swap(tDimHigh, tDimLow);
  if (tDimHigh < tLow || tDimLow > tHigh) return false;

  tLow = std::max(tDimLow, tLow);
  tHigh = std::min(tDimHigh, tHigh);
  if (tLow > tHigh) return false;

  return true;
}

bool HeightMap::hasIntersectionWithBoundingBox(const Ray &ray, float &tLow, float &tHigh) const {
  tLow = 0.f;
  tHigh = std::numeric_limits<float>::infinity();
  auto minToOrigin = aabbMin.getVectorBetween(ray.getOrigin());
  auto maxToOrigin = aabbMax.getVectorBetween(ray.getOrigin());

  auto dir = ray.getDirection();
  if (!findIntersectionInAxis(0, minToOrigin, maxToOrigin, dir, tLow, tHigh)
    || !findIntersectionInAxis(1, minToOrigin, maxToOrigin, dir, tLow, tHigh)
    || !findIntersectionInAxis(2, minToOrigin, maxToOrigin, dir, tLow, tHigh)) {
    return false;
  }

  return true;
}

HeightMap::HeightMap(const HeightMapReader &reader, const Point3d &position, unsigned width, unsigned height, unsigned depth, const Material &material)
  : position(position), height(height), width(width), depth(depth), material(material) {
  auto imgHeight = reader.getImageHeight(), imgWidth = reader.getImageWidth();
  map = std::vector<std::vector<Cell>>(imgHeight - 1);
  for (auto row = 0; row < imgHeight - 1; row++) {
    map[row] = std::vector<Cell>(imgWidth - 1);
    for (auto col = 0; col < imgWidth - 1; col++) {
      auto h = float(height);
      auto y = position.getY();
      float values[] = {
        reader.getIntensityAt(row, col) * h + y,
        reader.getIntensityAt(row, col + 1) * h + y,
        reader.getIntensityAt(row + 1, col) * h + y,
        reader.getIntensityAt(row + 1, col + 1) * h + y
      };
      auto xWidth = float(width) / float(imgWidth - 1);
      auto zDepth = float(depth) / float(imgHeight - 1);

      auto xPos = position.getX() + xWidth * col;
      auto zPos = position.getZ() + zDepth * row;
      map[row][col] = Cell(values[0], values[1], values[2], values[3], xPos, zPos, xWidth, zDepth);
    }
  }
  auto other = position + Point3d(float(width), float(height), float(depth));
  aabbMin = position.minimalCoords(other);
  aabbMax = position.maximalCoords(other);
}

std::string HeightMap::to_string() const {
  auto H = std::to_string(height), W = std::to_string(width), D = std::to_string(depth);
  std::string s = "heightMap(\r\n";
  for (const auto &row : map) {
    s += "  ";
    for (const auto &val : row) {
      s += val.to_string() + " ";
    }
    s += "\r\n";
  }
  s += ") with parameters (height, width, depth) set to (" + W + ", " + D + ", " + H + ") on position " + position.to_string();
  return s;
}
std::ostream &operator<<(std::ostream &out, const HeightMap &h) {
  out << h.to_string();
  return out;
}

const Point3d &HeightMap::getPosition() const {
  return position;
}

const Material &HeightMap::getMaterial() const {
  return material;
}

bool HeightMap::findIntersection(const Ray &ray, Intersection &intersection) const {
  float aabbTLow, aabbTHigh;
  if (!hasIntersectionWithBoundingBox(ray, aabbTLow, aabbTHigh)) return false;
  auto from = ray.getPointOnParameter(aabbTLow);
  auto to = ray.getPointOnParameter(aabbTHigh);
  // todo
  // find sequence of cells
  // find if there is intersection with bounding box of the cell (min ray height < max cell height)
  // if there is none, continue
  // if there is, find intersection with triangles, if there is, return, else continue in sequence


  // todo delete
//  Vector3d norm;
//  if(from.getX() == 180.f) norm = Vector3d(-1, 0, 0);
//  if(from.getX() == 380.f) norm = Vector3d(1, 0, 0);
//  if(from.getY() == 0.f) norm = Vector3d(0, -1, 0);
//  if(from.getY() == 160.f) norm = Vector3d(0, 1, 0);
//  if(from.getZ() == 250) norm = Vector3d(0, 0, -1);
//  if(from.getZ() == 50) norm = Vector3d(0, 0, 1);
//  intersection = Intersection(aabbTLow, norm);
//  return true;

  for (const auto &row : map) {
    for (auto col : row) {
      if (col.findIntersection(ray, intersection)) {
        return true;
      }
    }
  }
  return false;
}

