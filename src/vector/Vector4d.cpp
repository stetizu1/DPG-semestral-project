#include "Vector4d.h"

Vector4d::Vector4d(): x(0.f), y(0.f), z(0.f), w(1.f) {}

Vector4d::Vector4d(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4d::Vector4d(float arr[4]): x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}

Vector4d Vector4d::operator+(const Vector4d &other) const {
  return Vector4d(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4d Vector4d::operator-(const Vector4d &other) const {
  return Vector4d(x - other.x, y - other.y, z - other.z, w - other.w);
}

std::string Vector4d::to_string() const {
  auto X_S = std::to_string(x), Y_S = std::to_string(y), Z_S = std::to_string(z), W_S = std::to_string(w);
  return "vector4(" + X_S + ", " + Y_S + ", " + Z_S + ", " + W_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Vector4d &vector) {
  out << vector.to_string();
  return out;
}

float Vector4d::getX() const {
  return x;
}

float Vector4d::getY() const {
  return y;
}

float Vector4d::getZ() const {
  return z;
}

float Vector4d::getW() const {
  return w;
}

Point3d Vector4d::divideByW() const {
  return Point3d(x / w, y / w, z / w);
}

Vector3d Vector4d::ignoreW() const {
  return Vector3d(x, y, z);
}
float Vector4d::get(unsigned i) const {
  float v[4] = {x, y, z, w};
  return v[i];
}


