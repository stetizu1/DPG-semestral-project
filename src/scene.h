#pragma once

#include <vector>

#include "src/material/Material.h"
#include "src/heightmap/HeightMap.h"
#include "light/Light.h"


struct scene {
  /**
   * Definition of scene lights
   */
  static const Light lights[];

  /**
   * Definition of scene materials
   */
  static const Material materials[];

  /**
   * Definition of scene height maps
   */
   static const HeightMap heightMaps[];
};