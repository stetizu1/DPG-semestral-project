#pragma once

#include "src/point/Point3d.h"
#include "src/ray/Ray.h"

/**
 * Type for triangles
 *
 * Provides function to find intersection between triangle and ray
 */
class Triangle {
  Point3d basePoint;
  Vector3d vectors[2];

  Vector3d normal;

public:
  /**
   * Create triangle from base point and its' vectors
   * @param p - base point of triangle
   * @param v1 - first base vector of triangle
   * @param v2 - second base vector of triangle
   */
  explicit Triangle(const Point3d &p, const Vector3d &v1, const Vector3d &v2);

  /**
   * Create triangle from 3 points
   * @param p1 - first point, set as a base point
   * @param p2 - second point
   * @param p3 - third point
   */
  explicit Triangle(const Point3d &p1, const Point3d &p2, const Point3d &p3);

  /**
   * Create triangle from array with points, first is set as a base point
   * @param points - array of 3 points determining triangle
   */
  explicit Triangle(const Point3d points[]);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

  /**
   * Return triangle normal
   * @return normal of the triangle
   */
  [[nodiscard]] const Vector3d &getNormal() const;

  /**
   * Finds intersection of triangle and ray
   * @param ray - ray for which we are finding intersection
   * @param intersectionT - parameter of intersection if some is found
   * @return true if intersection is found
   */
  [[nodiscard]] bool getIntersection(const Ray &ray, float &intersectionT) const;
};
