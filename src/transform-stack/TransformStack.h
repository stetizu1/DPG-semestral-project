#pragma once

#include <stack>

#include "src/matrix/Matrix4d.h"

/**
 * Class storing matrix transformations
 */
class TransformStack {
  std::stack<Matrix4d> stack;

  /**
   * Replace top of the matrix with given one
   * @param matrix
   */
  void replaceTop(const Matrix4d &matrix);

public:
  /**
   * Create transform stack with identity matrix inside
   */
  explicit TransformStack();

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const TransformStack &transformStack);

  /**
   * Return top of the transform stack
   * @return
   */
  [[nodiscard]] Matrix4d top() const;

  /**
   * Multiply top with given matrix
   * @param matrix
   */
  void multiplyTop(const Matrix4d &matrix);
};
