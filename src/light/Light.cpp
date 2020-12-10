#include "Light.h"


Light::Light(const Point3d &position, const Color &colorIntensity) : position(position), colorIntensity(colorIntensity) {}

std::string Light::to_string() const {
  const std::string nl = "\r\n";
  auto s = "light(" + nl;
  s += "  position: " + position.to_string() + nl;
  s += "  color: " + colorIntensity.to_string() + nl;
  s += ")";
  return s;
}

std::ostream &operator<<(std::ostream &out, const Light &l) {
  out << l.to_string();
  return out;
}

const Color &Light::getColorIntensity() const {
  return colorIntensity;
}

const Point3d &Light::getPosition() const {
  return position;
}
