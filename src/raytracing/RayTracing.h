#pragma once

#include "src/context/Context.h"
#include "src/matrix/Matrix4d.h"
#include "src/vector/Vector4d.h"
#include "src/ray/Ray.h"

/**
 * Class for computing ray tracing for the screen
 */
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
  explicit RayTracing(Matrix4d inverseMatrix, Matrix4d inverseModelView, Context *context);

  /**
   * Computes ray tracing for screen space and saves it to color buffer in given context
   */
  void computeRayTrace() const;
};
