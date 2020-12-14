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

bool HeightMap::findIntersectionInYAxis(const Vector3d &minToOrigin, const Vector3d &maxToOrigin, const Vector3d &direction, float tLow, float tHigh) {
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
  if (!findIntersectionInYAxis(minToOrigin, maxToOrigin, dir, tLow, tHigh)) return false;

  return true;
}

bool HeightMap::checkRunX(int xFrom, int xTo, int currZ, float initY, float slopeY, const Ray &ray, Intersection &intersection, int sign) const {
  float rayMinY = std::min(initY + slopeY * float(xFrom) * widthRatio, initY + slopeY * float(xTo) * widthRatio);
  for (auto x = xFrom; x <= xTo; x++) {
    auto col = map[currZ][x];
    if (col.findIntersection(ray, intersection, rayMinY)) {
      return true;
    }
    // prevent rounding error
    if (currZ + sign < getMapHeight() && currZ + sign >= 0) {
      col = map[currZ + sign][x];
      if (col.findIntersection(ray, intersection, rayMinY)) {
        return true;
      }
    }
  }
  return false;
}

bool HeightMap::checkRunZ(int zFrom, int zTo, int currX, float initY, float slopeY, const Ray &ray, Intersection &intersection, int sign) const {
  float rayMinY = std::min(initY + slopeY * float(zFrom) * depthRatio, initY + slopeY * float(zTo) * depthRatio);
  zTo = std::min(int(zTo), int(getMapHeight()) - 1);
  for (auto z = zFrom; z <= zTo; z++) {
    auto col = map[z][currX];
    if (col.findIntersection(ray, intersection, rayMinY)) {
      return true;
    }
    // prevent rounding error
    if (currX + sign < getMapWidth() && currX + sign >= 0) {
      col = map[z][currX + sign];
      if (col.findIntersection(ray, intersection, rayMinY)) {
        return true;
      }
    }
  }
  return false;
}

bool HeightMap::checkIntersectionLine(const Point3d &from, const Ray &ray, Intersection &intersection) const {
  auto gridFrom = getBaseCoordinates(from);
  auto gridIntFrom = getIntBaseCoordinates(from);

  auto const x = gridIntFrom.getX();
  auto const realY = from.getY();
  auto const z = gridIntFrom.getZ();
  auto const slopeXY = ray.getDirection().getY() / ray.getDirection().getX();
  auto const slopeZY = ray.getDirection().getY() / ray.getDirection().getZ();

  if (x == 0) {
    auto b0 = gridFrom.getZ() - float(z);
    auto slope = ray.getDirection().getZ() / ray.getDirection().getX();

    auto slopeSign = (slope <= 0) ? -1 : 1;
    b0 = (slope <= 0) ? 1 - b0 : b0;
    slope = std::abs(slope);
    auto runLengthShort = int(std::floor(1 / slope));
    auto runLengthLong = int(std::ceil(1 / slope));
    if (runLengthShort >= getMapWidth()) {
      return checkRunX(0, int(getMapWidth()) - 1, x, realY, slopeXY, ray, intersection, slopeSign);
    }
    float v = 1 - slope * runLengthShort;
    int runLength;
    bool truncated = false;
    if (slope < 0.5f && b0 >= slope + v) { // truncated initial run
      auto dr = int(std::floor((b0 - v) / slope));
      b0 -= (v + dr * slope);
      truncated = true;
      runLength = runLengthShort - dr;
    } else {
      runLength = (b0 < v) ? runLengthLong : runLengthShort;
    }
    int currX = 0, currZ = z;
    float currB = b0;
    while (currX < getMapWidth() && currZ < getMapHeight() && currZ >= 0) {
      auto xFrom = (currX > 0 && currB > 0) ? currX - 1 : currX;
      auto xTo = std::min(currX + runLength, int(getMapWidth()) - 1);
      if (checkRunX(xFrom, xTo, currZ, realY, slopeXY, ray, intersection, slopeSign)) {
        return true;
      }
      currX += runLength;
      currZ += slopeSign;
      if (truncated) {
        truncated = false;
        currB = currB + slope * float(runLengthShort) - 1;
      } else {
        currB = currB + slope * float(runLength) - 1;
      }
      runLength = currB < v ? runLengthLong : runLengthShort;
    }
  }
  if (z == 0) {
    auto b0 = gridFrom.getX() - float(x);
    auto alpha = ray.getDirection().getX() / ray.getDirection().getZ();

    auto slopeSign = (alpha <= 0) ? -1 : 1;
    b0 = (alpha <= 0) ? 1 - b0 : b0;
    alpha = std::abs(alpha);
    auto runLengthShort = int(std::floor(1 / alpha));
    auto runLengthLong = int(std::ceil(1 / alpha));
    if (runLengthShort >= getMapHeight()) {
      return checkRunZ(0, int(getMapHeight()) - 1, x, realY, slopeZY, ray, intersection, slopeSign);
    }
    float v = 1 - alpha * runLengthShort;
    int runLength;
    bool truncated = false;
    if (alpha < 0.5f && b0 >= alpha + v) { // truncated initial run
      auto dr = int(std::floor((b0 - v) / alpha));
      b0 = b0 - (v + dr * alpha);
      truncated = true;
      runLength = runLengthShort - dr;
    } else {
      runLength = (b0 < v) ? runLengthLong : runLengthShort;
    }
    int currZ = 0, currX = x;
    float currB = b0;
    while (currZ < getMapWidth() && currX < getMapWidth() && currX >= 0) {
      auto zFrom = (currZ > 0 && currB > 0) ? currZ - 1 : currZ;
      auto zTo = currZ + std::min(runLength, int(getMapHeight()) - 1);
      if (checkRunZ(zFrom, zTo, currX, realY, slopeZY, ray, intersection, slopeSign)) {
        return true;
      }

      currZ += runLength;
      currX += slopeSign;
      if (truncated) {
        truncated = false;
        currB = currB + alpha * float(runLengthShort) - 1;
      } else {
        currB = currB + alpha * float(runLength) - 1;
      }
      runLength = currB < v ? runLengthLong : runLengthShort;
    }
  }
  return false;
}

HeightMap::HeightMap(const HeightMapReader &reader, const Point3d &position, unsigned width, unsigned height, unsigned depth, const Material &material)
  : position(position), height(height), width(width), depth(depth), material(material),
  widthRatio(float(width) / float(reader.getImageWidth() - 1)), depthRatio(float(depth) / float(reader.getImageHeight() - 1)) {
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

      auto xPos = position.getX() + widthRatio * col;
      auto zPos = position.getZ() + depthRatio * row;
      map[row][col] = Cell(values[0], values[1], values[2], values[3], xPos, zPos, widthRatio, depthRatio);
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

unsigned HeightMap::getMapHeight() const {
  return map.size();
}

unsigned HeightMap::getMapWidth() const {
  return map[0].size();
}

const Point3d &HeightMap::getPosition() const {
  return position;
}

const Material &HeightMap::getMaterial() const {
  return material;
}

Point2d HeightMap::getBaseCoordinates(const Point3d &pos) const {
  auto moved = pos - position;
  auto x = moved.getX() / widthRatio;
  auto z = moved.getZ() / depthRatio;
  return Point2d(x, z);
}

Point2i HeightMap::getIntBaseCoordinates(const Point3d &pos) const {
  auto base = getBaseCoordinates(pos);
  return Point2i(int(base.getX()), int(base.getZ()));
}

unsigned HeightMap::getHeight() const {
  return height;
}

bool HeightMap::findIntersection(const Ray &ray, Intersection &intersection) const {
  float aabbTLow, aabbTHigh;
  if (!hasIntersectionWithBoundingBox(ray, aabbTLow, aabbTHigh)) return false;
  const auto from = ray.getPointOnParameter(aabbTLow);
  return checkIntersectionLine(from, ray, intersection);
}


