#include "Triangle.h"

Triangle::Triangle(const Point3d &p, const Vector3d &v1, const Vector3d &v2) : basePoint(p), vectors{v1, v2} {
  normal = vectors[0].crossProduct(vectors[1]).normalized();
}

Triangle::Triangle(const Point3d &p1, const Point3d &p2, const Point3d &p3) : Triangle(p1, (p2 - p1).getAsVector(), (p3 - p1).getAsVector()) {}

Triangle::Triangle(const Point3d points[3]) : Triangle(points[0], points[1], points[2]) {}

std::string Triangle::to_string() const {
  const std::string nl = "\r\n";
  auto s = "triangle (" + nl;
  s += "  point: " + basePoint.to_string();
  s += "  vectors: " + vectors[0].to_string() + ", " + vectors[1].to_string();
  s += "  -- normal: " + normal.to_string();
  s += ")";
  return s;
}

std::ostream &operator<<(std::ostream &out, const Triangle &triangle) {
  out << triangle.to_string();
  return out;
}

const Vector3d &Triangle::getNormal() const {
  return normal;
}

bool Triangle::getIntersection(const Ray &ray, float &intersectionT) const {
  Vector3d s1 = ray.getDirection().crossProduct(vectors[1]);
  float divisor = s1.dotProduct(vectors[0]);
  if (divisor == 0.f) return false;

  float invertedDivisor = 1.f / divisor;
  Point3d d = ray.getOrigin() - basePoint;

  float b1 = d.getAsVector().dotProduct(s1) * invertedDivisor;
  if (b1 < 0.f || b1 > 1.f) return false;


  Vector3d s2 = d.getAsVector().crossProduct(vectors[0]);
  float b2 = ray.getDirection().dotProduct(s2) * invertedDivisor;
  if (b2 < 0.f || b1 + b2 > 1.f) return false;

  intersectionT = vectors[1].dotProduct(s2) * invertedDivisor;
  return true;
}




