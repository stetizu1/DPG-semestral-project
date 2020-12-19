#include "Material.h"

Material::Material(const Color &color, float kd, float ks, float shine)
  : color(color), kd(kd), ks(ks), shine(shine) {}

Material::Material(ColorChanging c) : color(), kd(1.f), ks(0), shine(0), changing(c) {}

std::string Material::to_string() const {
  if (isChangeColor()) {
    return "Material - changing: " + std::to_string(changing);
  }

  const std::string nl = "\r\n";
  auto s = "material(" + nl;
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

Color Material::getColor(float heightFactor) const {
  heightFactor *= 3;
  auto c1 = heightFactor > 1 ? 1 : heightFactor;
  auto c2 = heightFactor > 2 ? 1 : std::max(heightFactor - 1, 0.f);
  auto c3 = std::max(heightFactor - 2, 0.f);
  if (changing == ColorChanging::LAVA) {
    return Color(c1, c2, c3);
  }
  if (changing == ColorChanging::ICE) {
    return Color(c3, c2, c1);
  }
  return Color(c2, c1, c3);
}

bool Material::isChangeColor() const {
  return changing != ColorChanging::NONE;
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

