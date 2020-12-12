#include "RayTracing.h"
#include "src/illumination/Illumination.h"

RayTracing::RayTracing(const Matrix4d inverseMatrix, const Matrix4d inverseModelView, Context *context)
  : inverseMatrix(inverseMatrix), inverseModelView(inverseModelView), contextP(context) {}

void RayTracing::computeRayTrace() {
  auto rayOrigin = (inverseModelView * Vector4d(0, 0, 0, 1)).divideByW();
  auto dirX = (inverseMatrix * Vector4d(1.f, 0.f, 0.f, 0.f)).ignoreW();
  auto dirY = (inverseMatrix * Vector4d(0.f, 1.f, 0.f, 0.f)).ignoreW();

  auto dirO = (inverseMatrix * Vector4d(.5f, .5f, 1.f, 1.f)).divideByW().getVectorBetween(rayOrigin);
  for (auto y = 0; y < contextP->getHeight(); y++) {
    auto addY = dirY * y;
    auto minimalDir = dirO + addY;
    for (auto x = 0; x < contextP->getWidth(); x++) {
      auto rayDirection = (minimalDir + dirX * x).normalized();
      Ray ray(rayOrigin, rayDirection);
      auto intersection = contextP->getHeightMap()->findIntersection(ray);
      auto color = intersection.isExisting()
        ? Illumination::getDirectPhongIllumination(contextP->getLights(), contextP->getHeightMap()->getMaterial(), ray, intersection)
        : contextP->getBgColor();
      contextP->setToColorBuffer(x, y, color);
    }
  }
}

