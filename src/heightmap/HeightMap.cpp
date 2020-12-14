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
  tLow = 0.f;
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

bool HeightMap::checkRunX(unsigned xFrom, unsigned xTo, unsigned currZ, float initY, float slopeY, const Ray &ray, Intersection &intersection, int sign) const {
  float rayMinY = std::min(initY + slopeY * float(xFrom) * widthRatio, initY + slopeY * float(xTo) * widthRatio);
  for (auto x = xFrom; x <= xTo; x++) {
    auto col = map[currZ][x];
    if (col.findIntersection(ray, intersection, rayMinY)) {
      return true;
    }
    if (currZ + sign < getMapHeight() && currZ + sign >= 0) {
      col = map[currZ + sign][x];
      if (col.findIntersection(ray, intersection, rayMinY)) {
        return true;
      }
    }
  }
  return false;
}

bool HeightMap::checkRunZ(unsigned zFrom, unsigned zTo, unsigned currX, float initY, float slopeY, const Ray &ray, Intersection &intersection, int sign) const {
  float rayMinY = std::min(initY + slopeY * float(zFrom) * depthRatio, initY + slopeY * float(zTo) * depthRatio);
  for (auto z = zFrom; z <= zTo; z++) {
    auto col = map[z][currX];
    if (col.findIntersection(ray, intersection, rayMinY)) {
      return true;
    }
    if (currX + sign < getMapHeight() && currX + sign >= 0) {
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

  if (gridIntFrom.getX() == 0) {
    auto b0 = gridFrom.getZ() - float(gridIntFrom.getZ());
    auto alpha = ray.getDirection().getZ() / ray.getDirection().getX();
    auto slopeY = ray.getDirection().getY() / ray.getDirection().getX();

    if (alpha >= -1 && alpha <= 1) {
      auto diff = (alpha < 0) ? -1 : 1;
      b0 = (alpha <= 0) ? 1 - b0 : b0;
      alpha = std::abs(alpha);
      auto runLengthShort = int(std::floor(1 / alpha));
      auto runLengthLong = int(std::ceil(1 / alpha));
      if (runLengthShort >= getMapWidth()) {
        return checkRunX(0, getMapWidth() - 1, gridIntFrom.getZ(), from.getY(), slopeY, ray, intersection, diff);
      }
      float v = 1 - alpha * runLengthShort;
      unsigned runLength;
      bool truncated = false;
      if (alpha < 0.5f && b0 >= alpha + v) { // truncated initial run
        auto dr = int(std::floor((b0 - v) / alpha));
        b0 -= (v + dr * alpha);
        truncated = true;
        runLength = runLengthShort - dr;
      } else {
        runLength = (b0 < v) ? runLengthLong : runLengthShort;
      }
      unsigned currX = 0, currZ = gridIntFrom.getZ();
      float currB = b0;
      while (currX < getMapWidth() && currZ < getMapHeight() && currZ >= 0) {
        auto xFrom = (currX > 0 && currB > 0) ? currX - 1 : currX;
        auto xTo = std::min(currX + runLength, getMapWidth() - 1);
        if (checkRunX(xFrom, xTo, currZ, from.getY(), slopeY, ray, intersection, diff)) {
          return true;
        }
        currX += runLength;
        currZ += diff;
        if (truncated) {
          truncated = false;
          currB = currB + alpha * float(runLengthShort) - 1;
        } else {
          currB = currB + alpha * float(runLength) - 1;
        }
        runLength = currB < v ? runLengthLong : runLengthShort;
      }
    }
  }

  if (gridIntFrom.getZ() == 0) {
    auto b0 = gridFrom.getX() - float(gridIntFrom.getX());
    auto alpha = ray.getDirection().getX() / ray.getDirection().getZ();
    auto slopeY = ray.getDirection().getY() / ray.getDirection().getZ();

    if (alpha >= -1 && alpha <= 1) {
      auto diff = (alpha <= 0) ? -1 : 1;
      b0 = (alpha <= 0) ? 1 - b0 : b0;
      alpha = std::abs(alpha);
      auto runLengthShort = int(std::floor(1 / alpha));
      auto runLengthLong = int(std::ceil(1 / alpha));
      if (runLengthShort >= getMapHeight()) {
        return checkRunZ(0, getMapHeight() - 1, gridIntFrom.getX(), from.getY(), slopeY, ray, intersection, diff);
      }
      float v = 1 - alpha * runLengthShort;
      unsigned runLength;
      bool truncated = false;
      if (alpha < 0.5f && b0 >= alpha + v) { // truncated initial run
        auto dr = int(std::floor((b0 - v) / alpha));
        b0 = b0 - (v + dr * alpha);
        truncated = true;
        runLength = runLengthShort - dr;
      } else {
        runLength = (b0 < v) ? runLengthLong : runLengthShort;
      }
      unsigned currZ = 0, currX = gridIntFrom.getX();
      float currB = b0;
      while (currZ < getMapWidth() && currX < getMapWidth() && currX >= 0) {
        auto zFrom = (currZ > 0 && currB > 0) ? currZ - 1 : currZ;
        auto zTo = std::min(currZ + runLength, getMapHeight() - 1);
        if (checkRunZ(zFrom, zTo, currX, from.getY(), slopeY, ray, intersection, diff)) {
          return true;
        }
        currZ += runLength;
        currX += diff;
        if (truncated) {
          truncated = false;
          currB = currB + alpha * float(runLengthShort) - 1;
        } else {
          currB = currB + alpha * float(runLength) - 1;
        }
        runLength = currB < v ? runLengthLong : runLengthShort;
      }
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

Cell HeightMap::getCellOnPosition(const Point3d &pos) const {
  auto coordinates = getIntBaseCoordinates(pos);
  return map[coordinates.getX()][coordinates.getZ()];
}

bool HeightMap::findIntersection(const Ray &ray, Intersection &intersection) const {
  float aabbTLow, aabbTHigh;
  if (!hasIntersectionWithBoundingBox(ray, aabbTLow, aabbTHigh)) return false;
  const auto from = ray.getPointOnParameter(aabbTLow);
  if (checkIntersectionLine(from, ray, intersection)) {
    return true;
  }

  // todo
  // find sequence of cells
  // find if there is intersection with bounding box of the cell (min ray height < max cell height)
  // if there is none, continue
  // if there is, find intersection with triangles, if there is, return, else continue in sequence


  // todo delete
//  Vector3d norm = Vector3d(0, 0, 1);
//  intersection = Intersection(aabbTLow, norm);
//  return true;



//  for (const auto &row : map) {
//    for (auto col : row) {
//      if (col.findIntersection(ray, intersection)) {
//        return true;
//      }
//    }
//  }
  return false;
}


