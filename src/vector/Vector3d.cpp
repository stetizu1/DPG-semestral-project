#include "Vector3d.h"

Vector3d::Vector3d(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3d::Vector3d() : x(0.f), y(0.f), z(0.f) {}

Vector3d Vector3d::operator+(const Vector3d &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vector3d Vector3d::operator+=(const Vector3d &other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

Vector3d Vector3d::operator-(const Vector3d &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector3d Vector3d::operator-=(const Vector3d &other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

Vector3d Vector3d::operator*(float k) const {
  return {x * k, y * k, z * k};
}

Vector3d operator*(float k, const Vector3d &vector) {
  return {vector.x * k, vector.y * k, vector.z * k};
}

Vector3d Vector3d::operator*=(float k) {
  this->x *= k;
  this->y *= k;
  this->z *= k;
  return *this;
}

Vector3d Vector3d::operator/(float k) const {
  return {x / k, y / k, z / k};
}

Vector3d Vector3d::operator/=(float k) {
  this->x /= k;
  this->y /= k;
  this->z /= k;
  return *this;
}

std::string Vector3d::to_string() const {
  auto X_S = std::to_string(x), Y_S = std::to_string(y), Z_S = std::to_string(z);
  return "vector(" + X_S + ", " + Y_S + ", " + Z_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Vector3d &vector) {
  out << vector.to_string();
  return out;
}

Vector3d operator-(const Vector3d &vector) {
  return (-1) * vector;
}

float Vector3d::getX() const {
  return x;
}

float Vector3d::getY() const {
  return y;
}

float Vector3d::getZ() const {
  return z;
}

float Vector3d::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

float Vector3d::dotProduct(const Vector3d &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vector3d Vector3d::crossProduct(const Vector3d &other) const {
  auto ox = other.x, oy = other.y, oz = other.z;
  return {
    y * oz - z * oy,
    z * ox - x * oz,
    x * oy - y * ox,
  };
}

Vector3d Vector3d::normalized() const {
  auto l = length();
  return {x / l, y / l, z / l};
}
