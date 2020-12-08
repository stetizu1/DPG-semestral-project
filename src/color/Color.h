#pragma once

#include <string>
#include <ostream>

/**
 * Type for rgb color.
 *
 * Provides basic meaningful operation (+, -, *, /) with rgb color.
 */
class Color {
  float r, g, b;
public:
  /**
   * Create white color
   */
  explicit Color();

  /**
   * Create color with provided rgb values
   * @param r - red
   * @param g - green
   * @param b - blue
   */
  explicit Color(float r, float g, float b);

  Color operator+(const Color &other) const;
  Color operator+=(const Color &other);

  Color operator-(const Color &other) const;
  Color operator-=(const Color &other);

  Color operator*(const Color &other) const;
  Color operator*=(const Color &other);

  Color operator/(const Color &other) const;
  Color operator/=(const Color &other);

  Color operator*(float k) const;
  friend Color operator*(float k, const Color &color);
  Color operator*=(float k);

  Color operator/(float k) const;
  Color operator/=(float k);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &out, const Color &c);
};
