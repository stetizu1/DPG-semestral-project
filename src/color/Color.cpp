#include "Color.h"


Color::Color() : r(0.f), g(0.f), b(0.f) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color &other) const {
  return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator+=(const Color &other) {
  this->r += other.r;
  this->g += other.g;
  this->b += other.b;
  return *this;
}

Color Color::operator-(const Color &other) const {
  return Color(r - other.r, g - other.g, b - other.b);
}

Color Color::operator-=(const Color &other) {
  this->r -= other.r;
  this->g -= other.g;
  this->b -= other.b;
  return *this;
}

Color Color::operator*(const Color &other) const {
  return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*=(const Color &other) {
  this->r *= other.r;
  this->g *= other.g;
  this->b *= other.b;
  return *this;
}

Color Color::operator/(const Color &other) const {
  return Color(r / other.r, g / other.g, b / other.b);
}

Color Color::operator/=(const Color &other) {
  this->r /= other.r;
  this->g /= other.g;
  this->b /= other.b;
  return *this;
}

Color Color::operator*(float k) const {
  return Color(r * k, g * k, b * k);
}

Color operator*(float k, const Color &color) {
  return Color(color.r * k, color.g * k, color.b * k);
}

Color Color::operator*=(float k) {
  this->r *= k;
  this->g *= k;
  this->b *= k;
  return *this;
}

Color Color::operator/(float k) const {
  return Color(r / k, g / k, b / k);
}

Color Color::operator/=(float k) {
  this->r /= k;
  this->g /= k;
  this->b /= k;
  return *this;
}

std::string Color::to_string() const {
  auto const R_S = std::to_string(r), G_S = std::to_string(g), B_S = std::to_string(b);
  return "rgb(" + R_S + ", " + G_S + ", " + B_S + ")";
}

std::ostream &operator<<(std::ostream &out, const Color &c) {
  out << c.to_string();
  return out;
}
