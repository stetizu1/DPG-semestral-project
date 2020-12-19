#include "Point2d.h"

Point2d::Point2d(): x(0.f), z(0.f) {}

Point2d::Point2d(float x, float z): x(x), z(z) {}


Point2d Point2d::operator+(const Point2d &other) const {
  return Point2d(x + other.x, z + other.z);
}

Point2d Point2d::operator+=(const Point2d &other) {
  this->x += other.x;
  this->z += other.z;
  return *this;
}

Point2d Point2d::operator-(const Point2d &other) const {
  return Point2d(x - other.x, z - other.z);
}

Point2d Point2d::operator-=(const Point2d &other) {
  this->x -= other.x;
  this->z -= other.z;
  return *this;
}

Point2d Point2d::operator*(float k) const {
  return Point2d(x * k, z * k);
}

Point2d operator*(float k, const Point2d &point) {
  return Point2d(point.x * k, point.z * k);
}

Point2d Point2d::operator*=(float k) {
  this->x *= k;
  this->z *= k;
  return *this;
}

Point2d Point2d::operator/(float k) const {
  return Point2d(x / k, z / k);
}

Point2d Point2d::operator/=(float k) {
  this->x /= k;
  this->z /= k;
  return *this;
}


std::string Point2d::to_string() const {
  auto X_S = std::to_string(x), Z_S = std::to_string(z);
  return "point(" + X_S + ", " + Z_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Point2d &point) {
  out << point.to_string();
  return out;
}

float Point2d::getX() const {
  return x;
}

float Point2d::getZ() const {
  return z;
}

Point2d Point2d::invertX() const {
  return Point2d(-x, z);
}

Point2d Point2d::invertZ() const {
  return Point2d(x, -z);
}


