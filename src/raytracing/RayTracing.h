#pragma once

#include "src/context/Context.h"
#include "src/matrix/Matrix4d.h"
#include "src/vector/Vector4d.h"
#include "src/ray/Ray.h"

class RayTracing {
  Matrix4d inverseMatrix;
  Matrix4d inverseModelView;
  Context *contextP;

public:
  /**
   * Create structure for ray tracing
   * @param inverseMatrix - inverted viewport projection * inverted model view projection
   * @param inverseModelView - inverted model view
   * @param context - scene context
   */
  RayTracing(Matrix4d inverseMatrix, Matrix4d inverseModelView, Context *context);

  void computeRayTrace();
};
