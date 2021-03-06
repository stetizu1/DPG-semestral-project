#include "Point3d.h"

Point3d::Point3d() : x(0.f), y(0.f), z(0.f) {}

Point3d::Point3d(float x, float y, float z) : x(x), y(y), z(z) {}


Point3d Point3d::operator+(const Point3d &other) const {
  return Point3d(x + other.x, y + other.y, z + other.z);
}

Point3d Point3d::operator+=(const Point3d &other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

Point3d Point3d::operator-(const Point3d &other) const {
  return Point3d(x - other.x, y - other.y, z - other.z);
}

Point3d Point3d::operator-=(const Point3d &other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

Point3d Point3d::operator*(float k) const {
  return Point3d(x * k, y * k, z * k);
}

Point3d operator*(float k, const Point3d &point) {
  return Point3d(point.x * k, point.y * k, point.z * k);
}

Point3d Point3d::operator*=(float k) {
  this->x *= k;
  this->y *= k;
  this->z *= k;
  return *this;
}

Point3d Point3d::operator/(float k) const {
  return Point3d(x / k, y / k, z / k);
}

Point3d Point3d::operator/=(float k) {
  this->x /= k;
  this->y /= k;
  this->z /= k;
  return *this;
}

Point3d Point3d::operator+(const Vector3d &vector) const {
  return *this + Point3d(vector.getX(), vector.getY(), vector.getZ());
}

Point3d operator+(Vector3d &vector, const Point3d &point) {
  return point + Point3d(vector.getX(), vector.getY(), vector.getZ());
}

Point3d Point3d::operator+=(const Vector3d &vector) {
  this->x += vector.getX();
  this->y += vector.getY();
  this->z += vector.getZ();
  return *this;
}

Point3d Point3d::operator-(const Vector3d &vector) const {
  return *this - Point3d(vector.getX(), vector.getY(), vector.getZ());
}

Vector3d operator-(Vector3d &vector, const Point3d &point) {
  return Vector3d(vector.getX() - point.x, vector.getY() - point.y, vector.getZ() - point.z);
}

Point3d Point3d::operator-=(const Vector3d &vector) {
  this->x -= vector.getX();
  this->y -= vector.getY();
  this->z -= vector.getZ();
  return *this;
}

std::string Point3d::to_string() const {
  auto X_S = std::to_string(x), Y_S = std::to_string(y), Z_S = std::to_string(z);
  return "point(" + X_S + ", " + Y_S + ", " + Z_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Point3d &point) {
  out << point.to_string();
  return out;
}

float Point3d::getX() const {
  return x;
}

float Point3d::getY() const {
  return y;
}

float Point3d::getZ() const {
  return z;
}

float Point3d::get(unsigned i) const {
  float p[] = {x, y, z};
  return p[i];
}

Point3d Point3d::minimalCoords(Point3d &other) const {
  return Point3d(std::min(x, other.x), std::min(y, other.y), std::min(z, other.z));
}

Point3d Point3d::maximalCoords(Point3d &other) const {
  return Point3d(std::max(x, other.x), std::max(y, other.y), std::max(z, other.z));
}

Vector3d Point3d::getVectorBetween(const Point3d &other) const {
  return Vector3d(x - other.x, y - other.y, z - other.z);
}

Vector3d Point3d::getNormalizedVectorBetween(const Point3d &other) const {
  return getVectorBetween(other).normalized();
}
