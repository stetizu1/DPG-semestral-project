#include "Light.h"


Light::Light(const Point3d &position, const Color &colorIntensity) : position(position), colorIntensity(colorIntensity) {}

const Color &Light::getColorIntensity() const {
  return colorIntensity;
}
const Point3d &Light::getPosition() const {
  return position;
}
