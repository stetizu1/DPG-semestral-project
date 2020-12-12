#pragma once

#include <vector>

#include "src/color/Color.h"
#include "src/material/Material.h"
#include "src/heightmap/HeightMap.h"
#include "light/Light.h"


struct scene {
  /**
   * Default width of the window
   */
  constexpr static const unsigned defaultWidth = 512;

  /**
   * Default height of the window
   */
  constexpr static const unsigned defaultHeight = 512;

  /**
   * Field of view, angles in degrees
   */
  constexpr static const unsigned fov = 40;

  /**
   * Z near for perspective view
   */
  constexpr static const float zNear = 1.f;

  /**
  * Z far for perspective view
  */
  constexpr static const float zFar = 1800.f;


  /**
  * Default center point
   */
  const static Point3d defaultCenter;

  /**
   * Default eye position
   */
  const static Vector3d defaultEye;


  /**
   * Default up vector
   */
  const static Vector3d defaultUp;

  /**
   * Default color of the background
   */
  const static Color defaultBgColor;

  /**
   * Definition of scene lights
   */
  static const std::vector<Light> lights;

  /**
   * Definition of scene materials
   */
  static const std::vector<Material> materials;

  /**
   * Definition of scene height maps
   */
  static const std::vector<HeightMap> heightMaps;
};