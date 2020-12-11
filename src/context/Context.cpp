#include "Context.h"

Context::Context(unsigned width, unsigned height)
  : width(width), height(height), colorBuffer(height),
  viewport{0, 0, float(width) / 2.f, float(height) / 2.f},
  lights(scene::lights) {
  for (auto i = 0; i < height; i++) colorBuffer[i] = std::vector<Color>(width);

  auto h = tan(scene::fov / 2) * scene::zNear, w = h * float(width) / float(height);
  projection.multiplyTop(Matrix4d::getProjectionMatrix(-w, w, -h, h, scene::zNear, scene::zFar));

  lookAt(scene::defaultCenter, scene::defaultEye, scene::defaultUp);
}

Context::Context() : Context(scene::defaultWidth, scene::defaultHeight) {}

const std::vector<Light> &Context::getLights() const {
  return lights;
}

void Context::addHeightMap(const HeightMap &heightMap) {
  heightMaps.emplace_back(heightMap);
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

const std::vector<std::vector<Color>> &Context::getColorBuffer() const {
  return colorBuffer;
}

void Context::rayTrace() {
  auto mvTop = modelView.top();
  auto invertedMvTop = mvTop.getInverted();
}

