#include "Material.h"

Material::Material(const Color &color, float kd, float ks, float shine)
  : color(color), kd(kd), ks(ks), shine(shine) {}

Material::Material(): color(), kd(1.f), ks(0), shine(0), changeColor(true) {}

std::string Material::to_string() const {
  const std::string nl = "\r\n";
  auto s = "light(" + nl;
  s += "  color: " + color.to_string() + nl;
  s += "  kd: " + std::to_string(kd) + nl;
  s += "  ks: " + std::to_string(ks) + nl;
  s += "  shine: " + std::to_string(shine) + nl;
  s += ")";
  return s;
}

std::ostream &operator<<(std::ostream &out, const Material &m) {
  out << m.to_string();
  return out;
}

const Color &Material::getColor() const {
  return color;
}

Color Material::getColor(float heightFactor) {
  heightFactor *= 3;
  auto r = heightFactor > 1 ? 1 : heightFactor;
  auto g = heightFactor > 2 ? 1 : std::max(heightFactor - 1, 0.f);
  auto b = std::max(heightFactor - 2, 0.f);
  return Color(r, g, b);
}

bool Material::isChangeColor() const {
  return changeColor;
}

float Material::getKd() const {
  return kd;
}

float Material::getKs() const {
  return ks;
}

float Material::getShine() const {
  return shine;
}

