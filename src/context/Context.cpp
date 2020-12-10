#include "Context.h"

Context::Context() {
  lights = scene::lights;
}
const std::vector<Light> &Context::getLights() const {
  return lights;
}

