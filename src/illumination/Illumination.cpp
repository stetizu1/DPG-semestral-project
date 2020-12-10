#include "Illumination.h"

Color Illumination::getDirectPhongIllumination(const Context &context, const Material &material, const Triangle &triangle, const Ray &ray, float t) {
  auto color = Color(0, 0, 0);
  auto intersectPoint = ray.getPointOnParameter(t);

  auto normal = triangle.getNormal();
  for (auto light : context.getLights()) {
    auto directionToViewer = -ray.getDirection();
    auto directionToLight = light.getPosition().getNormalizedVectorBetween(intersectPoint);
    auto directionOfReflectedLight = (normal * (2.f * directionToLight.dotProduct(normal))) - directionToLight;

    auto cosAlpha = normal.dotProduct(directionToLight);
    auto cosBeta = std::max(directionToViewer.dotProduct(directionOfReflectedLight), 0.f);

    color += light.getColorIntensity() * material.getColor() * (material.getKd() * cosAlpha); // diffuse
    color += light.getColorIntensity() * material.getKs() * std::pow(cosBeta, material.getShine()); // specular
  }
  return color;
}
