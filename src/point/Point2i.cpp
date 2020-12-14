#include "Point2i.h"

Point2i::Point2i(): x(0.f), z(0.f) {}

Point2i::Point2i(int x, int z): x(x), z(z) {}


Point2i Point2i::operator+(const Point2i &other) const {
  return Point2i(x + other.x, z + other.z);
}

Point2i Point2i::operator+=(const Point2i &other) {
  this->x += other.x;
  this->z += other.z;
  return *this;
}

Point2i Point2i::operator-(const Point2i &other) const {
  return Point2i(x - other.x, z - other.z);
}

Point2i Point2i::operator-=(const Point2i &other) {
  this->x -= other.x;
  this->z -= other.z;
  return *this;
}

Point2i Point2i::operator*(int k) const {
  return Point2i(x * k, z * k);
}

Point2i operator*(int k, const Point2i &point) {
  return Point2i(point.x * k, point.z * k);
}

Point2i Point2i::operator*=(int k) {
  this->x *= k;
  this->z *= k;
  return *this;
}


std::string Point2i::to_string() const {
  auto X_S = std::to_string(x), Z_S = std::to_string(z);
  return "point(" + X_S + ", " + Z_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Point2i &point) {
  out << point.to_string();
  return out;
}

int Point2i::getX() const {
  return x;
}

int Point2i::getZ() const {
  return z;
}