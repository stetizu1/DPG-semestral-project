#pragma once

#include <string>
#include <ostream>

/**
 * Type for 2D integer point
 *
 * Provides basic meaningful operation (+, -, *) for point
 */
class Point2i {
  int x, z;

public:
  /**
   * Creates point in coordinate origin
   * @return 
   */
  explicit Point2i();
  /**
   * Create point with provided x, z coordinates.
   * @param x - x coordinate
   * @param z - z coordinate
   */
  explicit Point2i(int x, int z);

  Point2i operator+(const Point2i &other) const;
  Point2i operator+=(const Point2i &other);

  Point2i operator-(const Point2i &other) const;
  Point2i operator-=(const Point2i &other);

  Point2i operator*(int k) const;
  friend Point2i operator*(int k, const Point2i &point);
  Point2i operator*=(int k);

  bool operator==(Point2i &other) const;
  bool operator!=(Point2i &other) const;
  

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Point2i &point);

  /**
   * Get x coordinate of the point
   * @return x coordinate
   */
  [[nodiscard]] int getX() const;

  /**
   * Get z coordinate of the point
   * @return z coordinate
   */
  [[nodiscard]] int getZ() const;
};
