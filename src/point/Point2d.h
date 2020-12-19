#pragma once

#include <string>
#include <ostream>

/**
 * Type for 2D point
 *
 * Provides basic meaningful operation (+, -, *, /) for point
 */
  class Point2d {
    float x, z;

  public:
    /**
     * Creates point in coordinate origin
     * @return 
     */
    explicit Point2d();
    /**
     * Create point with provided x, z coordinates.
     * @param x - x coordinate
     * @param z - z coordinate
     */
    explicit Point2d(float x, float z);

    Point2d operator+(const Point2d &other) const;
    Point2d operator+=(const Point2d &other);

    Point2d operator-(const Point2d &other) const;
    Point2d operator-=(const Point2d &other);

    Point2d operator*(float k) const;
    friend Point2d operator*(float k, const Point2d &point);
    Point2d operator*=(float k);

    Point2d operator/(float k) const;
    Point2d operator/=(float k);

    [[nodiscard]] std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &out, const Point2d &point);

    /**
     * Get x coordinate of the point
     * @return x coordinate
     */
    [[nodiscard]] float getX() const;

    /**
     * Get z coordinate of the point
     * @return z coordinate
     */
    [[nodiscard]] float getZ() const;

    /**
     * Get point with swapped coordinates (z, x)
     * @return swapped point
     */
    [[nodiscard]] Point2d swapped() const;

    /**
     * Get point with inverted x (-x, z)
     * @return point with inverted x
     */
    [[nodiscard]] Point2d invertX() const;

    /**
     * Get point with inverted z (x, -z)
     * @return point with inverted z
     */
    [[nodiscard]] Point2d invertZ() const;
  };
