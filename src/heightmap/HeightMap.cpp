#include "HeightMap.h"

bool HeightMap::findIntersectionInAxis(unsigned d, const Vector3d &minToOrigin, const Vector3d &maxToOrigin, const Vector3d &direction, float &tLow, float &tHigh) {
  float tDimLow = minToOrigin.get(d) / direction.get(d);
  float tDimHigh = maxToOrigin.get(d) / direction.get(d);

  if (tDimHigh < tDimLow) std::swap(tDimHigh, tDimLow);
  if (tDimHigh < tLow || tDimLow > tHigh) return false;

  tLow = std::max(tDimLow, tLow);
  tHigh = std::min(tDimHigh, tHigh);
  if (tLow > tHigh) return false;

  return true;
}

bool HeightMap::hasHeightIntersection(const Vector3d &minToOrigin, const Vector3d &maxToOrigin, const Vector3d &direction, float tLow, float tHigh) {
  float tDimLow = minToOrigin.getY() / direction.getY();
  float tDimHigh = maxToOrigin.getY() / direction.getY();
  if (tDimHigh < tDimLow) std::swap(tDimHigh, tDimLow);
  if (tDimHigh < tLow || tDimLow > tHigh || std::max(tDimLow, tLow) > std::min(tDimHigh, tHigh)) return false;
  return true;
}

bool HeightMap::hasIntersectionWithBoundingBox(const Ray &ray, float &tLow, float &tHigh) const {
  tLow = std::numeric_limits<float>::lowest();
  tHigh = std::numeric_limits<float>::infinity();
  auto minToOrigin = aabbMin.getVectorBetween(ray.getOrigin());
  auto maxToOrigin = aabbMax.getVectorBetween(ray.getOrigin());

  auto dir = ray.getDirection();
  if (!findIntersectionInAxis(0, minToOrigin, maxToOrigin, dir, tLow, tHigh)
    || !findIntersectionInAxis(2, minToOrigin, maxToOrigin, dir, tLow, tHigh)) {
    return false;
  }
  // does not change parameters tLow, tHigh, so it have to be last
  if (!hasHeightIntersection(minToOrigin, maxToOrigin, dir, tLow, tHigh)) return false;

  return true;
}

HeightMap::HeightMap(const MapReader &reader, const Point3d &position, float width, float height, float depth, const Material &material)
  : GridIntersection(reader, height, float(width) / float(reader.getImageWidth() - 1),  float(depth) / float(reader.getImageHeight() - 1), position),
  height(height), width(width), depth(depth), material(material) {
  auto other = position + Point3d(width, height, depth);
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

float HeightMap::getHeightFraction(float y) const {
  return (y - position.getY()) / height;
}

bool HeightMap::findIntersection(const Ray &ray, Intersection &intersection) const {
  float aabbTLow, aabbTHigh;
  if (!hasIntersectionWithBoundingBox(ray, aabbTLow, aabbTHigh)) return false;
  const auto from = ray.getPointOnParameter(aabbTLow);
  const auto to = ray.getPointOnParameter(aabbTHigh);
  return findRayIntersection(from, to, ray, intersection);
}


