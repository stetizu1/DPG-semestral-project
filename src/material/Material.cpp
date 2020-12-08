#include "Material.h"

Material::Material(const Color &color, float kd, float ks, float shine)
  : color(color), kd(kd), ks(ks), shine(shine) {}

const Color &Material::getColor() const {
  return color;
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

