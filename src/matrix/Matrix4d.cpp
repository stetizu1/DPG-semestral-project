#include <iostream>
#include "Matrix4d.h"

void Matrix4d::getCofactor(const float matrixData[4][4], float cofactor[4][4], int r, int c, int n) {
  int i = 0, j = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (row != r && col != c) {
        cofactor[i][j] = matrixData[row][col];
        j++;
        if (j == n - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

float Matrix4d::getDeterminant(const float matrixData[4][4], int n) const {
  float determinant = 0.f;
  if (n == 1) return matrixData[0][0];

  float cofactors[4][4];
  float sign = 1.f;

  for (int f = 0; f < n; f++) {
    getCofactor(matrixData, cofactors, 0, f, n);
    determinant += sign * matrixData[0][f] * getDeterminant(cofactors, n - 1);
    sign = -sign;
  }
  return determinant;
}

Matrix4d Matrix4d::getAdj() const {
  Matrix4d adj;
  float sign;
  float cof[4][4];

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      getCofactor(data, cof, r, c);
      sign = ((r + c) % 2 == 0) ? 1.f : -1.f;
      adj.data[c][r] = sign * (getDeterminant(cof, 3));
    }
  }
  return adj;
}

Matrix4d::Matrix4d() : data{{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}} {}
Matrix4d::Matrix4d(float d[4][4]) : data{
  {d[0][0], d[0][1], d[0][2], d[0][3]},
  {d[1][0], d[1][1], d[1][2], d[1][3]},
  {d[2][0], d[2][1], d[2][2], d[2][3]},
  {d[3][0], d[3][1], d[3][2], d[3][3]}} {}

Vector4d Matrix4d::operator*(const Vector4d &vector) const {
  float result[4] = {0, 0, 0, 0};
  for (auto r1 = 0; r1 < 4; r1++) {
    for (auto c1 = 0; c1 < 4; c1++) {
      result[r1] += this->data[r1][c1] * vector.get(c1);
    }
  }
  return Vector4d(result);
}

Matrix4d Matrix4d::operator*(const Matrix4d &matrix) const {
  Matrix4d result = Matrix4d();
  for (auto r1 = 0; r1 < 4; r1++)
    for (auto c2 = 0; c2 < 4; c2++)
      for (auto c1 = 0; c1 < 4; c1++)
        result.data[r1][c2] += this->data[r1][c1] * matrix.data[c1][c2];
  return result;
}

std::string Matrix4d::to_string() const {
  std::string res_string = "matrix(\r\n";
  for (auto row : data) {
    res_string += "   ";
    for (auto val_idx = 0; val_idx < 4; val_idx++) res_string += std::to_string(row[val_idx]) + " ";
    res_string += "\r\n";
  }
  res_string += ")";
  return res_string;
}

std::ostream &operator<<(std::ostream &out, const Matrix4d &matrix) {
  out << matrix.to_string();
  return out;
}

Matrix4d Matrix4d::getTransposed() const {
  Matrix4d result = Matrix4d();
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      result.data[row][col] = data[col][row];
    }
  }
  return result;
}

Matrix4d Matrix4d::getInverted() const {
  float determinant = getDeterminant(this->data);
  if (determinant == 0.f) {
    std::cerr << "Matrix to invert was singular!";
    throw std::invalid_argument("Matrix given to invert is singular");
  }
  std::cout << determinant << " det ";

  Matrix4d inverted;
  Matrix4d adj = getAdj();
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      inverted.data[row][col] = adj.data[row][col] / determinant;
  return inverted;
}


Matrix4d Matrix4d::getIdentityMatrix() {
  float mData[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getTranslateMatrix(float x, float y, float z) {
  float mData[4][4] = {
    {1, 0, 0, x},
    {0, 1, 0, y},
    {0, 0, 1, z},
    {0, 0, 0, 1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getRotateXMatrix(float angle) {
  auto cos_a = std::cos(angle);
  auto sin_a = std::sin(angle);
  float mData[4][4] = {
    {1, 0,     0,      0},
    {0, cos_a, -sin_a, 0},
    {0, sin_a, cos_a,  0},
    {0, 0,     0,      1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getRotateYMatrix(float angle) {
  auto cos_a = std::cos(angle);
  auto sin_a = std::sin(angle);
  float mData[4][4] = {
    {cos_a,  0, sin_a, 0},
    {0,      1, 0,     0},
    {-sin_a, 0, cos_a, 0},
    {0,      0, 0,     1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getRotateZMatrix(float angle) {
  auto cos_a = std::cos(angle);
  auto sin_a = std::sin(angle);
  float mData[4][4] = {
    {cos_a, -sin_a, 0, 0},
    {sin_a, cos_a,  0, 0},
    {0,     0,      1, 0},
    {0,     0,      0, 1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getScaledMatrix(float scaleX, float scaleY, float scaleZ) {
  float mData[4][4] = {
    {scaleX, 0,      0,      0},
    {0,      scaleY, 0,      0},
    {0,      0,      scaleZ, 0},
    {0,      0,      0,      1},
  };
  return Matrix4d(mData);
}

Matrix4d Matrix4d::getProjectionMatrix(float l, float r, float b, float t, float n, float f) {
  float mData[4][4] = {
    {2 * n / (r - l), 0,               (r + l) / (r - l), 0},
    {0,               2 * n / (t - b), (t + b) / (t - b), 0},
    {0,               0,               (n + f) / (n - f), (2 * n * f) / (n - f)},
    {0,               0,               -1,                0},
  };
  return Matrix4d(mData);
}
