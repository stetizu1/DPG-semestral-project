#pragma once

#include <ostream>

/**
 * Type for storing rational numbers, providing operations with them.
 * Does not normalizeRational to minimal value.
 */
class Rational {
  int numerator;
  int denominator;

  friend void normalizeRational(Rational &rational);
  void normalize();

  /**
   * Create rational number with nominator and denominator, already checked for existence
   * @param n - nominator
   * @param d - denominator
   * @param checked - true if already normalized
   */
  Rational(int n, int d, bool checked);
public:
  /**
   * Create rational number with nominator and denominator, if it does exist
   * @param n - nominator
   * @param d - denominator
   */
  Rational(int n, int d);

  Rational operator+(const Rational &other) const;
  Rational operator-(const Rational &other) const;
  Rational operator*(const Rational &other) const;
  Rational operator/(const Rational &other) const;

  Rational operator+(int k) const;
  Rational operator-(int k) const;
  Rational operator*(int k) const;
  Rational operator/(int k) const;

  friend Rational operator+(int k, const Rational &rational);
  friend Rational operator-(int k, const Rational &rational);
  friend Rational operator*(int k, const Rational &rational);
  friend Rational operator/(int k, const Rational &rational);

  friend Rational operator-(const Rational &rational);

  Rational operator+=(const Rational &other);
  Rational operator-=(const Rational &other);
  Rational operator*=(const Rational &other);
  Rational operator/=(const Rational &other);
  Rational operator+=(int num);
  Rational operator-=(int num);
  Rational operator*=(int num);
  Rational operator/=(int num);


  bool operator<(int num) const;
  bool operator>(int num) const;
  bool operator<=(int num) const;
  bool operator>=(int num) const;

  friend bool operator<(int num, const Rational &rational);
  friend bool operator>(int num, const Rational &rational);
  friend bool operator<=(int num, const Rational &rational);
  friend bool operator>=(int num, const Rational &rational);

  bool operator<(const Rational &rational) const;
  bool operator>(const Rational &rational) const;
  bool operator<=(const Rational &rational) const;
  bool operator>=(const Rational &rational) const;

  bool operator==(const Rational &rational) const;
  bool operator!=(const Rational &rational) const;

  bool operator==(int num) const;
  bool operator!=(int num) const;

  friend bool operator==(int num, const Rational &rational);
  friend bool operator!=(int num, const Rational &rational);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &os, const Rational &rational);

  /**
   * Get rational as float
   * @return float representing rational
   */
  [[nodiscard]] float getFloat() const;
};

