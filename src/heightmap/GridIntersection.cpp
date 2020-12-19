#include "GridIntersection.h"
#include "src/scene.h"
#include "src/rational/Rational.h"

GridIntersection::Transformation::Transformation(bool swapXz, bool plusX, bool plusZ, const Point2i &first) : swapXZ(swapXz), plusX(plusX), plusZ(plusZ), first(first) {}

bool GridIntersection::findIntersectionInRun(const Transformation &transformation, int from, int to, int otherCoord, float initY, float stepY, const Ray &ray, Intersection &intersection) const {
  auto diff = from < to ? 1 : -1;
  int i = stepY > 0 ? from : from + 1;
  auto isVertical = !transformation.swapXZ;
  if (isVertical) {
    auto anotherCoord = transformation.plusZ ? otherCoord : int(getGridDepth()) - otherCoord - 1;
    if (anotherCoord < 0)return false;
    for (auto x = from; x != to + diff; x += diff, i++) { // until equals (including equals)
      auto minHeight = initY + float(i) * stepY;
      if (map[anotherCoord][x].findIntersection(ray, intersection, minHeight)) {
        return true;
      }
    }
  } else {
    auto anotherCoord = transformation.plusX ? otherCoord : transformation.first.getX() - (otherCoord - transformation.first.getX());
    if (anotherCoord < 0)return false;
    for (auto z = from; z != to + diff; z += diff, i++) { // until equals (including equals)
      auto minHeight = initY + float(i) * stepY;
      if (map[z][anotherCoord].findIntersection(ray, intersection, minHeight)) {
        return true;
      }
    }
  }
  return false;
}

bool
GridIntersection::findBasicRayIntersection(const Transformation &transformation, const Point2d &from, float initY, float stepY, const Point2d &gridRay, const Ray &ray, Intersection &intersection) const {
  auto coordFrom = getGridCoordinates(from);

  auto alpha = Rational(int(gridRay.getZ() * scene::precision), int(gridRay.getX() * scene::precision));
  int runLengthShort = std::floor((1 / alpha).getFloat());
  int runLengthLong = std::ceil((1 / alpha).getFloat());
  auto v = 1 - alpha * runLengthShort;
  auto last = int(getGridWidth()) - 1;

  auto beta = Rational(int((from.getZ() - float(coordFrom.getZ())) * scene::precision), scene::precision);
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

GridIntersection::GridIntersection(const MapReader &reader, float height, float cellW, float cellD, const Point3d &position) : Grid(reader, height, cellW, cellD, position) {}

int GridIntersection::checkVerticalAndHorizontalIntersection(const Point2d &gridPointFrom, const Point2d &gridPointTo, float initY, float toY, const Ray &ray, Intersection &intersection) const {
  auto gridCoordinateFrom = getGridCoordinates(gridPointFrom);
  auto gridCoordinateTo = getGridCoordinates(gridPointTo);
  if (gridCoordinateFrom.getZ() == gridCoordinateTo.getZ()
    && ((gridCoordinateFrom.getX() == 0 && gridCoordinateTo.getX() == int(getGridWidth()) - 1) || (gridCoordinateFrom.getX() == int(getGridWidth()) - 1) && gridCoordinateTo.getX() == 0)) {
    auto stepY = (initY - toY) / (gridPointFrom.getX() - gridPointTo.getX());
    auto isIntersecting = findIntersectionInRun(Transformation(false, gridCoordinateFrom.getX() == 0, true, gridCoordinateFrom), gridCoordinateFrom.getX(), gridCoordinateTo.getX(), gridCoordinateFrom.getZ(), initY, stepY, ray,
      intersection);
    return isIntersecting ? 1 : -1;
  }
  if (gridCoordinateFrom.getX() == gridCoordinateTo.getX()
    && ((gridCoordinateFrom.getZ() == 0 && gridCoordinateTo.getZ() == int(getGridWidth()) - 1) || (gridCoordinateFrom.getZ() == int(getGridWidth()) - 1) && gridCoordinateTo.getZ() == 0)) {
    auto stepY = (initY - toY) / (gridPointFrom.getZ() - gridPointTo.getZ());
    auto isIntersecting = findIntersectionInRun(Transformation(true, true, gridCoordinateFrom.getZ() == 0, gridCoordinateFrom), gridCoordinateFrom.getZ(), gridCoordinateTo.getZ(), gridCoordinateFrom.getX(), initY, stepY, ray, intersection);
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


  auto alpha = Rational(int(gridRay.getZ() * scene::precision), int(gridRay.getX() * scene::precision));

  if (gridRay.getX() > 0) {
    auto stepXY = (ray.getDirection().getY() / ray.getDirection().getX()) * cellWidth;
    if ((alpha > 0) && (alpha <= 1)) {
      return findBasicRayIntersection(Transformation(false, true, true, gridCoordinateFrom), gridPointFrom, initY, stepXY, gridRay, ray, intersection);
    } else if ((alpha > -1) && (alpha < 0)) {
      gridPointFrom = Point2d(gridPointFrom.getX(), float(getGridDepth()) - gridPointFrom.getZ());
      return findBasicRayIntersection(Transformation(false, true, false, gridCoordinateFrom), gridPointFrom, initY, stepXY, gridRay.invertZ(), ray, intersection);
    }
  }


  return false;
}
