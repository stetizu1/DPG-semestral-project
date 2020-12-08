#pragma once

#include "src/vector/Vector4d.h"

/**
 * Type for transformation matrices.
 * Provides static functions for basic matrix transformation (identity, translate, rotate (x, y, z), scale)
 * Provides multiplication by other matrix or by 4d vector, transposition and inverting
 */
class Matrix4d {
  float data[4][4];
  /**
   * Save cofactors to given matrix
   * @param cofactors - matrix data where cofactors are saved
   * @param r - row
   * @param c - column
   */
  static void getCofactor(const float matrixData[4][4], float cofactors[4][4], int r, int c, int n = 4);
  /**
   * Get adjacent matrix
   * @return adjacent matrix
   */
  [[nodiscard]] Matrix4d getAdj() const;
  /**
   * Get determinant of given matrix
   * @param matrix - matrix we are finding determinant to
   * @param n - size of matrix
   * @return
   */
  [[nodiscard]] float getDeterminant(const float matrixData[4][4], int n = 4) const;

public:
  /**
   * Create empty 4d matrix full of 0s
   */
  explicit Matrix4d();
  /**
   * Create matrix with given data
   * @param data
   */
  explicit Matrix4d(float data[4][4]);

  Vector4d operator*(const Vector4d &vector) const;
  Matrix4d operator*(const Matrix4d &matrix) const;

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Matrix4d &matrix);

  /**
   * Return transposed matrix
   * @return transposed version of matrix
   */
  [[nodiscard]] Matrix4d getTransposed() const;

  /**
   * Get inverted matrix
   * @return inverted matrix
   */
  [[nodiscard]] Matrix4d getInverted() const;

  /**
   * Get identity matrix
   * @return identity matrix
   */
  [[nodiscard]] static Matrix4d getIdentityMatrix() ;

  /**
   * Get matrix representing translation by (x, y, z)
   * @param x - translation in x axis
   * @param y - translation in y axis
   * @param z - translation in z axis
   * @return matrix of translation
   */
  [[nodiscard]] static Matrix4d getTranslateMatrix(float x, float y, float z) ;

  /**
   * Get matrix representing rotation in X axis
   * @param angle - size of angle to rotate
   * @return matrix of rotation in X axis
   */
  [[nodiscard]] static Matrix4d getRotateXMatrix(float angle) ;
  /**
   * Get matrix representing rotation in Y axis
   * @param angle - size of angle to rotate
   * @return matrix of rotation in Y axis
   */
  [[nodiscard]] static Matrix4d getRotateYMatrix(float angle) ;
  /**
   * Get matrix representing rotation in Z axis
   * @param angle - size of angle to rotate
   * @return matrix of rotation in Z axis
   */
  [[nodiscard]] static Matrix4d getRotateZMatrix(float angle) ;

  /**
   * Get matrix representing scaling by (x, y, z)
   * @param scaleX - scale in x axis
   * @param scaleY - scale in y axis
   * @param scaleZ - scale in z axis
   * @return matrix representing scaling
   */
  [[nodiscard]] static Matrix4d getScaledMatrix(float scaleX, float scaleY, float scaleZ);

  /**
   * Get matrix of perspective projection
   * @param left - left x coordinate
   * @param right - right x coordinate
   * @param bottom - bottom y coordinate
   * @param top - top y coordinate
   * @param near - near dist
   * @param far - far dist
   * @return matrix of perspective projection
   */
  [[nodiscard]] static Matrix4d getProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
};
