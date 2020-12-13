#pragma once

#include "src/matrix/Matrix4d.h"

/**
 * Class to store viewport and getting viewport matrix
 */
class Viewport {
  int x, y;
  float fx, fy;
  float w2, h2;
public:
  /**
   * Create viewport
   * @param x - viewport x
   * @param y - viewport y
   * @param w2 - viewport width / 2
   * @param h2 - viewport height / 2
   */
  explicit Viewport(int x, int y, float w2, float h2);

  /**
   * Create viewport matrix and return it
   * @return viewport matrix
   */
  Matrix4d getViewportMatrix();
};
