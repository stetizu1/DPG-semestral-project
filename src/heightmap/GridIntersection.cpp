#include "GridIntersection.h"
#include "src/scene.h"
#include "src/rational/Rational.h"

GridIntersection::Transformation::Transformation(bool horizontal, bool positive) : horizontal(horizontal), positive(positive) {}

bool GridIntersection::findIntersectionInRun(const Transformation &transformation, int from, int to, int otherCoord, float initY, float stepY, const Ray &ray, Intersection &intersection) const {
  auto diff = from < to ? 1 : -1;
  int i = stepY > 0 ? from : from + 1;
  if (transformation.horizontal) {
    auto z = transformation.positive ? otherCoord : int(getGridDepth()) - otherCoord - 1;
    for (auto x = from; x != to + diff; x += diff, i++) { // until equals (including equals)
      auto minHeight = initY + float(i) * stepY;
      if (map[z][x].findIntersection(ray, intersection, minHeight)) {
        return true;
      }
    }
  } else {
    auto x = transformation.positive ? otherCoord : int(getGridWidth()) - otherCoord - 1;
    for (auto z = from; z != to + diff; z += diff, i++) { // until equals (including equals)
      auto minHeight = initY + float(i) * stepY;
      if (map[z][x].findIntersection(ray, intersection, minHeight)) {
        return true;
      }
    }
  }
  return false;
}

bool
GridIntersection::findBasicRayIntersectionX(const Transformation &transformation, const Point2d &from, float initY, float stepY, const Point2d &gridRay, const Ray &ray, Intersection &intersection) const {
  auto coordFrom = getGridCoordinates(from);

  auto alpha = Rational(long(gridRay.getZ() * scene::precision), long(gridRay.getX() * scene::precision));
  int runLengthShort = std::floor((1 / alpha).getFloat());
  int runLengthLong = std::ceil((1 / alpha).getFloat());
  auto v = 1 - alpha * runLengthShort;
  auto last = int(getGridWidth()) - 1;

  auto beta = Rational(long((from.getZ() - float(coordFrom.getZ())) * scene::precision), scene::precision);
  auto currInterceptBeta = beta;
  auto currX = coordFrom.getX(), currZ = coordFrom.getZ(), currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  if (beta >= alpha + v) { // if first run is truncated
    int lengthOfTruncated = std::ceil(((1 - beta) / alpha).getFloat());
    if (findIntersectionInRun(transformation, coordFrom.getX(), std::min(lengthOfTruncated, last), currZ, initY, stepY, ray, intersection)) {
      return true;
    }
    currX += lengthOfTruncated;
    currZ++;
    currInterceptBeta = (beta - v) - (alpha * std::floor(((beta - v) / alpha).getFloat()));
    currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  }

  while (currX < getGridWidth() && currZ < getGridDepth()) {
    if (findIntersectionInRun(transformation, std::max(coordFrom.getX(), currX - 1), std::min(currX + currRunLength, last), currZ, initY, stepY, ray, intersection)) {
      return true;
    }
    currX += currRunLength;
    currZ++;
    currInterceptBeta += alpha * currRunLength - 1;
    currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  }
  return false;
}

bool GridIntersection::findBasicRayIntersectionZ(const GridIntersection::Transformation &transformation, const Point2d &from, float initY, float stepY, const Point2d &gridRay, const Ray &ray, Intersection &intersection) const {
  auto coordFrom = getGridCoordinates(from);

  auto alpha = Rational(long(gridRay.getX() * scene::precision), long(gridRay.getZ() * scene::precision));
  int runLengthShort = std::floor((1 / alpha).getFloat());
  int runLengthLong = std::ceil((1 / alpha).getFloat());
  auto v = 1 - alpha * runLengthShort;
  auto last = int(getGridDepth()) - 1;

  auto beta = Rational(long((from.getX() - float(coordFrom.getX())) * scene::precision), scene::precision);
  auto currInterceptBeta = beta;
  auto currZ = coordFrom.getZ(), currX = coordFrom.getX(), currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  if (beta >= alpha + v) { // if first run is truncated
    int lengthOfTruncated = std::ceil(((1 - beta) / alpha).getFloat());
    if (findIntersectionInRun(transformation, coordFrom.getZ(), std::min(lengthOfTruncated, last), currX, initY, stepY, ray, intersection)) {
      return true;
    }
    currZ += lengthOfTruncated;
    currX++;
    currInterceptBeta = (beta - v) - (alpha * std::floor(((beta - v) / alpha).getFloat()));
    currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  }

  while (currZ < getGridDepth() && currX < getGridWidth()) {
    if (findIntersectionInRun(transformation, std::max(coordFrom.getZ(), currZ - 1), std::min(currZ + currRunLength, last), currX, initY, stepY, ray, intersection)) {
      return true;
    }
    currZ += currRunLength;
    currX++;
    currInterceptBeta += alpha * currRunLength - 1;
    currRunLength = (currInterceptBeta < v) ? runLengthLong : runLengthShort;
  }
  return false;
}

GridIntersection::GridIntersection(const MapReader &reader, float height, float cellW, float cellD, const Point3d &position) : Grid(reader, height, cellW, cellD, position) {}

int GridIntersection::checkVerticalAndHorizontalIntersection(const Point2d &gridPointFrom, const Point2d &gridPointTo, float initY, float toY, const Ray &ray, Intersection &intersection) const {
  auto gridCoordinateFrom = getGridCoordinates(gridPointFrom);
  auto gridCoordinateTo = getGridCoordinates(gridPointTo);
  if (gridCoordinateFrom.getZ() == gridCoordinateTo.getZ()
    && ((gridCoordinateFrom.getX() == 0 && gridCoordinateTo.getX() == int(getGridWidth()) - 1) || (gridCoordinateFrom.getX() == int(getGridWidth()) - 1) && gridCoordinateTo.getX() == 0)) {
    auto stepY = (initY - toY) / (gridPointFrom.getX() - gridPointTo.getX());
    auto isIntersecting = findIntersectionInRun(Transformation(true, gridCoordinateFrom.getX() == 0), gridCoordinateFrom.getX(), gridCoordinateTo.getX(), gridCoordinateFrom.getZ(), initY, stepY, ray,
      intersection);
    return isIntersecting ? 1 : -1;
  }
  if (gridCoordinateFrom.getX() == gridCoordinateTo.getX()
    && ((gridCoordinateFrom.getZ() == 0 && gridCoordinateTo.getZ() == int(getGridWidth()) - 1) || (gridCoordinateFrom.getZ() == int(getGridWidth()) - 1) && gridCoordinateTo.getZ() == 0)) {
    auto stepY = (initY - toY) / (gridPointFrom.getZ() - gridPointTo.getZ());
    auto isIntersecting = findIntersectionInRun(Transformation(false, gridCoordinateFrom.getZ() == 0), gridCoordinateFrom.getZ(), gridCoordinateTo.getZ(), gridCoordinateFrom.getX(), initY, stepY, ray, intersection);
    return isIntersecting ? 1 : -1;
  }
  return 0;
}

bool GridIntersection::findRayIntersection(const Point3d &from, const Point3d &to, const Ray &ray, Intersection &intersection) const {
  auto gridPointFrom = getGridPoint(from);
  auto gridPointTo = getGridPoint(to);
  auto gridRay = gridPointTo - gridPointFrom;
  auto gridCoordinateFrom = getGridCoordinates(from);
  auto initY = from.getY();

  // prevent dividing by 0
  auto isIntersectingHorVer = checkVerticalAndHorizontalIntersection(gridPointFrom, gridPointTo, initY, to.getY(), ray, intersection);
  if (isIntersectingHorVer != 0) return isIntersectingHorVer == 1;

  auto stepZY = (ray.getDirection().getY() / std::abs(ray.getDirection().getZ())) * cellDepth;
  auto stepXY = (ray.getDirection().getY() / std::abs(ray.getDirection().getX())) * cellWidth;

  if (gridCoordinateFrom.getX() == 0) {
    auto alpha = Rational(long(gridRay.getZ() * scene::precision), long(gridRay.getX() * scene::precision));
    if (alpha > 0) {
      auto stepY = (alpha < 1) ? stepZY : stepXY;
      return findBasicRayIntersectionX(Transformation(true, true), gridPointFrom, initY, stepY, gridRay, ray, intersection);
    } else {
      gridPointFrom = Point2d(gridPointFrom.getX(), float(getGridDepth()) - gridPointFrom.getZ());
      auto stepY = (alpha > -1) ? stepZY : stepXY;
      return findBasicRayIntersectionX(Transformation(true, false), gridPointFrom, initY, stepY, gridRay.invertZ(), ray, intersection);
    }
  }
  if (gridCoordinateFrom.getZ() == 0) {
    auto alpha = Rational(long(gridRay.getX() * scene::precision), long(gridRay.getZ() * scene::precision));
    if (alpha > 0) {
      auto stepY = (alpha < 1) ? stepXY : stepZY;
      return findBasicRayIntersectionZ(Transformation(false, true), gridPointFrom, initY, stepY, gridRay, ray, intersection);
    } else {
      gridPointFrom = Point2d((float(getGridWidth()) - gridPointFrom.getX()), gridPointFrom.getZ());
      auto stepY = (alpha > -1) ? stepXY : stepZY;
      return findBasicRayIntersectionZ(Transformation(false, false), gridPointFrom, initY, stepY, gridRay.invertX(), ray, intersection);
    }
  }
  return false;
}
