#include "Cell.h"

Cell::Cell(float topLeft, float topRight, float bottomLeft, float bottomRight, float xPos, float zPos, float width, float depth) : topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {
  maxHeight = std::max(std::max(topLeft, topRight), std::max(bottomLeft, bottomRight));

  auto p1 = Point3d(xPos, topLeft, zPos);
  auto p2 = Point3d(xPos + width, bottomRight, zPos + depth);
  auto pC1 = Point3d(xPos + width, topRight, zPos);
  auto pC2 = Point3d(xPos, bottomLeft, zPos + depth);
  triangles = {
    Triangle(p1, pC2.getVectorBetween(p1), pC1.getVectorBetween(p1)),
    Triangle(p2, pC1.getVectorBetween(p2), pC2.getVectorBetween(p2))
  };
}

std::string Cell::to_string() const {
  return "{"
    + std::to_string(topLeft).substr(0, 4) + ","
    + std::to_string(topRight).substr(0, 4) + ","
    + std::to_string(bottomLeft).substr(0, 4) + ","
    + std::to_string(bottomRight).substr(0, 4) + " --> "
    + std::to_string(maxHeight).substr(0, 4)
    + "} ";
}

std::ostream &operator<<(std::ostream &out, const Cell &cell) {
  out << cell.to_string();
  return out;
}

float Cell::getMaxHeight() const {
  return maxHeight;
}

bool Cell::findIntersection(const Ray &ray, Intersection &intersection) {
  float t;
  auto isWithFirst = triangles[0].getIntersection(ray, t);
  if (isWithFirst) {
    intersection = Intersection(t, triangles[0].getNormal());
    return true;
  }
  auto isWithSecond = triangles[1].getIntersection(ray, t);
  if (isWithSecond) {
    intersection = Intersection(t, triangles[1].getNormal());
    return true;
  }
  return false;
}
