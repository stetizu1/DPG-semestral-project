#include "TransformStack.h"

TransformStack::TransformStack() {
  stack.push(Matrix4d::getIdentityMatrix());
}

void TransformStack::pushMatrix(const Matrix4d &matrix) {
  stack.emplace(matrix);
}

void TransformStack::popMatrix() {
  stack.pop();
  if (stack.empty()) {
    stack.emplace(Matrix4d::getIdentityMatrix());
  }
}

Matrix4d TransformStack::top() const {
  return stack.top();
}

void TransformStack::replaceTop(const Matrix4d& matrix) {
  popMatrix();
  pushMatrix(matrix);
}

void TransformStack::multiplyTop(const Matrix4d &matrix) {
  replaceTop(top() * matrix);
}
