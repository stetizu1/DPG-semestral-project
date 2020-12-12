#include "Viewport.h"

Viewport::Viewport(int x, int y, float w2, float h2) : x(x), y(y), w2(w2), h2(h2) {
  fx = float(x);
  fy = float(y);
}

Matrix4d Viewport::getViewportMatrix() {
  float data[4][4] = {
    {w2, 0,  0, w2 + fx},
    {0,  h2, 0, h2 + fy},
    {0,  0,  1, 0},
    {0,  0,  0, 1},
  };
  return Matrix4d(data);
}
