#include <iostream>
#include "Illumination.h"

Color Illumination::getDirectPhongIllumination(const std::vector<Light> &lights, const Material &material, const Ray &ray, const Intersection &intersection, float heightFactor) {
  auto color = Color(0, 0, 0);
  auto intersectPoint = ray.getPointOnParameter(intersection.getT());
  auto normal = intersection.getNormal();

  for (auto light : lights) {
    auto directionToViewer = -ray.getDirection();
    auto directionToLight = light.getPosition().getNormalizedVectorBetween(intersectPoint);
    auto directionOfReflectedLight = (normal * (2.f * directionToLight.dotProduct(normal))) - directionToLight;

    auto cosAlpha = normal.dotProduct(directionToLight);
    auto cosBeta = std::max(directionToViewer.dotProduct(directionOfReflectedLight), 0.f);

    auto matColor = material.isChangeColor() ? material.getColor(heightFactor) : material.getColor();
    color += light.getColorIntensity() * matColor * (material.getKd() * cosAlpha); // diffuse
    color += light.getColorIntensity() * material.getKs() * std::pow(cosBeta, material.getShine()); // specular
  }
  return color;
}
