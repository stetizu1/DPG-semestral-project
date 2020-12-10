#pragma once

#include <stack>

#include "src/matrix/Matrix4d.h"

class TransformStack {
  std::stack<Matrix4d> stack;

public:
  /**
   * Create transform stack with identity matrix inside
   */
  explicit TransformStack();

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const TransformStack &transformStack);

  /**
   * Push given matrix on the top of the stack
   * @param matrix
   */
  void pushMatrix(const Matrix4d &matrix);

  /**
   * Pop matrix from the stack
   */
  void popMatrix();

  /**
   * Return top of the transform stack
   * @return
   */
  [[nodiscard]] Matrix4d top() const;

  /**
   * Replace top of the matrix with given one
   * @param matrix
   */
  void replaceTop(const Matrix4d &matrix);

  /**
   * Multiply top with given matrix
   * @param matrix
   */
  void multiplyTop(const Matrix4d &matrix);
};
