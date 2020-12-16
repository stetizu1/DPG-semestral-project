#include "Cell.h"

Cell::Cell(float topLeft, float topRight, float bottomLeft, float bottomRight, float xPos, float zPos, float width, float depth) {
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
    + triangles[0].to_string() + " "
    + triangles[1].to_string() + " with max height "
    + std::to_string(maxHeight)
    + "} ";
}

std::ostream &operator<<(std::ostream &out, const Cell &cell) {
  out << cell.to_string();
  return out;
}

bool Cell::findIntersection(const Ray &ray, Intersection &intersection, float minHeight) {
  if (minHeight > maxHeight) return false;
  float t;
  if (triangles[0].getIntersection(ray, t)) {
    intersection = Intersection(t, triangles[0].getNormal());
    return true;
  }
  if (triangles[1].getIntersection(ray, t)) {
    intersection = Intersection(t, triangles[1].getNormal());
    return true;
  }
  return false;
}
