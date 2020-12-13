#include "TransformStack.h"

void TransformStack::replaceTop(const Matrix4d& matrix) {
  stack.pop();
  stack.emplace(matrix);
}

TransformStack::TransformStack() {
  stack.push(Matrix4d::getIdentityMatrix());
}

std::string TransformStack::to_string() const {
  const std::string nl = "\r\n";
  auto s = "transform stack(" + nl;
  s += "  top: " + top().to_string();
  s += ")";
  return s;
}

std::ostream &operator<<(std::ostream &out, const TransformStack &transformStack) {
  out << transformStack.to_string();
  return out;
}

Matrix4d TransformStack::top() const {
  return stack.top();
}

void TransformStack::multiplyTop(const Matrix4d &matrix) {
  replaceTop(top() * matrix);
}
