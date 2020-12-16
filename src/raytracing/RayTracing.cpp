#include "RayTracing.h"
#include "src/illumination/Illumination.h"

RayTracing::RayTracing(const Matrix4d inverseMatrix, const Matrix4d inverseModelView, Context *context)
  : inverseMatrix(inverseMatrix), inverseModelView(inverseModelView), contextP(context) {}

void RayTracing::computeRayTrace() const {
  auto rayOrigin = (inverseModelView * Vector4d(0, 0, 0, 1)).divideByW();
  auto dirX = (inverseMatrix * Vector4d(1.f, 0.f, 0.f, 0.f)).ignoreW();
  auto dirY = (inverseMatrix * Vector4d(0.f, 1.f, 0.f, 0.f)).ignoreW();
  auto dirO = (inverseMatrix * Vector4d(.5f, .5f, -1.f, 1.f)).divideByW().getVectorBetween(rayOrigin);

  for (auto y = 0; y < contextP->getHeight(); y++) {
    auto addY = dirY * y;
    auto minimalDir = dirO + addY;
    for (auto x = 0; x < contextP->getWidth(); x++) {
      auto rayDirection = (minimalDir + dirX * x).normalized();
      Ray ray(rayOrigin, rayDirection);
      Intersection intersection;
      auto hasIntersection = contextP->getHeightMap()->findIntersection(ray, intersection);
      auto color = contextP->getBgColor();
      if (hasIntersection) {
        auto intersectPoint = ray.getPointOnParameter(intersection.getT());
        auto heightFactor = contextP->getHeightMap()->getHeightFraction(intersectPoint.getY());
        color = Illumination::getDirectPhongIllumination(contextP->getLights(), contextP->getHeightMap()->getMaterial(), ray, intersection, heightFactor);
        for (auto &light : contextP->getLights()) {
          auto shadowRay = Ray(light.getPosition(), (intersectPoint.getNormalizedVectorBetween(light.getPosition())));
          Intersection shadowIntersection;
          auto hasShadowIntersection = contextP->getHeightMap()->findIntersection(shadowRay, shadowIntersection);
          if (!hasShadowIntersection) continue;

          auto shIntersectPoint = shadowRay.getPointOnParameter(shadowIntersection.getT());
          auto coords = contextP->getHeightMap()->getGridCoordinates(intersectPoint);
          auto shCoords = contextP->getHeightMap()->getGridCoordinates(shIntersectPoint);
          if (shCoords != coords) {
            color *= 0.1f; // leave some color
          }
        }
      }
      contextP->setToColorBuffer(x, y, color);
    }
  }
}

