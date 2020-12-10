#pragma once

#include <vector>

#include "src/light/Light.h"
#include "src/scene.h"

class Context {
  std::vector<Light> lights;

public:
  Context();

  const std::vector<Light> &getLights() const;
};