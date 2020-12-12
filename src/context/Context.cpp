#include "Context.h"
#include "src/raytracing/RayTracing.h"


Context::Context(unsigned int width, unsigned int height, const HeightMap *heightMap, const Color &bgColor)
  : width(width), height(height), colorBuffer(height),
  heightMap(heightMap),
  bgColor(bgColor),
  viewport{0, 0, float(width) / 2.f, float(height) / 2.f},
  lights(scene::lights) {
  for (auto i = 0; i < height; i++) colorBuffer[i] = std::vector<Color>(width);

  auto h = tan(scene::fov / 2) * scene::zNear, w = h * float(width) / float(height);
  projection.multiplyTop(Matrix4d::getProjectionMatrix(-w, w, -h, h, scene::zNear, scene::zFar));

  lookAt(scene::defaultCenter, scene::defaultEye, scene::defaultUp);
  rayTrace();
}

Context::Context() : Context(scene::defaultWidth, scene::defaultHeight, &scene::heightMaps[0], scene::defaultBgColor) {}

const std::vector<Light> &Context::getLights() const {
  return lights;
}

const std::vector<std::vector<Color>> &Context::getColorBuffer() const {
  return colorBuffer;
}

unsigned Context::getWidth() const {
  return width;
}

unsigned Context::getHeight() const {
  return height;
}

const HeightMap *Context::getHeightMap() const {
  return heightMap;
}

const Color &Context::getBgColor() const {
  return bgColor;
}

void Context::setToColorBuffer(unsigned int x, unsigned int y, const Color &color) {
  colorBuffer[x][y] = color;
}

void Context::lookAt(Point3d center, Vector3d eye, Vector3d up) {
  auto z = (eye - center).normalized();
  auto x = up.crossProduct(z).normalized();
  auto y = z.crossProduct(x).normalized();

  float data[4][4] = {
    {x.getX(), x.getY(), x.getZ(), -eye.dotProduct(x)},
    {y.getX(), y.getY(), y.getZ(), -eye.dotProduct(y)},
    {z.getX(), z.getY(), z.getZ(), -eye.dotProduct(z)},
    {0,        0,        0,        1},
  };
  Matrix4d matrix(data);
  modelView.multiplyTop(matrix);
}

void Context::rayTrace() {
  auto modelViewProjection = modelView.top();
  auto invertedModelViewProjection = modelViewProjection.getInverted();

  auto viewportProjection = projection.top() * viewport.getViewportMatrix();
  auto invertedViewportProjection = viewportProjection.getInverted();

  auto invertedMatrix = invertedViewportProjection * invertedModelViewProjection;
  RayTracing rayTracing(invertedMatrix, invertedModelViewProjection, this);
  rayTracing.computeRayTrace();
}

