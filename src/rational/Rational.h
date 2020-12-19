#pragma once

#include <ostream>

/**
 * Type for storing rational numbers, providing operations with them.
 * Does not normalizeRational to minimal value.
 */
class Rational {
  long long numerator;
  long long denominator;

  friend void normalizeRational(Rational &rational);
  void normalize();

  /**
   * Create rational number with nominator and denominator, already checked for existence
   * @param n - nominator
   * @param d - denominator
   * @param checked - true if already normalized
   */
  Rational(long long n, long long d, bool checked);
public:
  /**
   * Create rational number with nominator and denominator, if it does exist
   * @param n - nominator
   * @param d - denominator
   */
  Rational(long long n, long long d);

  Rational operator+(const Rational &other) const;
  Rational operator-(const Rational &other) const;
  Rational operator*(const Rational &other) const;
  Rational operator/(const Rational &other) const;

  Rational operator+(long long k) const;
  Rational operator-(long long k) const;
  Rational operator*(long long k) const;
  Rational operator/(long long k) const;

  friend Rational operator+(long long k, const Rational &rational);
  friend Rational operator-(long long k, const Rational &rational);
  friend Rational operator*(long long k, const Rational &rational);
  friend Rational operator/(long long k, const Rational &rational);

  friend Rational operator-(const Rational &rational);

  Rational operator+=(const Rational &other);
  Rational operator-=(const Rational &other);
  Rational operator*=(const Rational &other);
  Rational operator/=(const Rational &other);
  Rational operator+=(long long num);
  Rational operator-=(long long num);
  Rational operator*=(long long num);
  Rational operator/=(long long num);


  bool operator<(long long num) const;
  bool operator>(long long num) const;
  bool operator<=(long long num) const;
  bool operator>=(long long num) const;

  friend bool operator<(long long num, const Rational &rational);
  friend bool operator>(long long num, const Rational &rational);
  friend bool operator<=(long long num, const Rational &rational);
  friend bool operator>=(long long num, const Rational &rational);

  bool operator<(const Rational &rational) const;
  bool operator>(const Rational &rational) const;
  bool operator<=(const Rational &rational) const;
  bool operator>=(const Rational &rational) const;

  bool operator==(const Rational &rational) const;
  bool operator!=(const Rational &rational) const;

  bool operator==(long long num) const;
  bool operator!=(long long num) const;

  friend bool operator==(long long num, const Rational &rational);
  friend bool operator!=(long long num, const Rational &rational);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &os, const Rational &rational);

  /**
   * Get rational as float
   * @return float representing rational
   */
  [[nodiscard]] float getFloat() const;
};

