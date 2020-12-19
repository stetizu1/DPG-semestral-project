#include <iostream>
#include <string>
#include "Rational.h"

void normalizeRational(Rational &rational) {
  if (rational.numerator == 0) {
    rational.denominator = 1;
    return;
  }
  long long a = std::abs(rational.numerator), b = rational.denominator;
  long long remainder;
  while (b != 0) {
    remainder = a % b;
    a = b;
    b = remainder;
  }
  rational.numerator /= a;
  rational.denominator /= a;
}

void Rational::normalize() {
  normalizeRational(*this);
}

Rational::Rational(long long n, long long d, bool checked) : numerator(n) {
  if (!checked) {
    if (d < 0) {
      numerator *= -1;
      denominator = -d;
    } else {
      denominator = d;
    }
  } else {
    denominator = d;
  }
  normalize();
}

Rational::Rational(long long n, long long d) : Rational(n, d, false) {
  if (d == 0) {
    std::cerr << "Rational can not have 0 as denominator (increase precision)";
    throw std::invalid_argument("0 denominator given");
  }
}


Rational Rational::operator+(const Rational &other) const {
  return Rational(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator, true);
}

Rational Rational::operator-(const Rational &other) const {
  return Rational(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator, true);
}

Rational Rational::operator*(const Rational &other) const {
  return Rational(numerator * other.numerator, denominator * other.denominator, true);
}

Rational Rational::operator/(const Rational &other) const {
  return Rational(numerator * other.denominator, denominator * other.numerator, false);
}

Rational Rational::operator+(long long k) const {
  return Rational(numerator + k * denominator, denominator, true);
}
Rational Rational::operator-(long long k) const {
  return Rational(numerator - k * denominator, denominator, true);
}
Rational Rational::operator*(long long k) const {
  return Rational(numerator * k, denominator, true);
}
Rational Rational::operator/(long long k) const {
  if (k == 0) {
    std::cerr << "Rational can not be divided by 0";
    throw std::invalid_argument("tried to divide by 0");
  }
  return Rational(numerator, k * denominator, false);
}
Rational operator+(long long k, const Rational &rational) {
  return rational + k;
}
Rational operator-(long long k, const Rational &rational) {
  return Rational(k * rational.denominator - rational.numerator, rational.denominator, false);
}
Rational operator*(long long k, const Rational &rational) {
  return rational * k;
}

Rational operator/(long long k, const Rational &rational) {
  return Rational(k * rational.denominator, rational.numerator, false);
}

Rational operator-(const Rational &rational) {
  return Rational(rational.numerator * -1, rational.denominator, true);
}

Rational Rational::operator+=(const Rational &other) {
  auto res = *this + other;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}
Rational Rational::operator-=(const Rational &other) {
  auto res = *this - other;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}
Rational Rational::operator*=(const Rational &other) {
  auto res = *this * other;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

Rational Rational::operator/=(const Rational &other) {
  auto res = *this / other;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

Rational Rational::operator+=(long long num) {
  auto res = *this + num;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

Rational Rational::operator-=(long long num) {
  auto res = *this - num;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

Rational Rational::operator*=(long long num) {
  auto res = *this * num;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

Rational Rational::operator/=(long long num) {
  auto res = *this / num;
  numerator = res.numerator;
  denominator = res.denominator;
  return *this;
}

bool Rational::operator<(long long num) const {
  return getFloat() < float(num);
}

bool Rational::operator>(long long num) const {
  return num < *this;
}

bool Rational::operator<=(long long num) const {
  return !(num < *this);
}

bool Rational::operator>=(long long num) const {
  return !(*this < num);
}

bool operator<(long long num, const Rational &rational) {
  return float(num) < rational.getFloat();
}

bool operator>(long long num, const Rational &rational) {
  return num < rational;
}

bool operator<=(long long num, const Rational &rational) {
  return !(num < rational);
}

bool operator>=(long long num, const Rational &rational) {
  return !(rational < num);
}

bool Rational::operator<(const Rational &rational) const {
  return getFloat() < rational.getFloat();
}

bool Rational::operator>(const Rational &rational) const {
  return rational < *this;
}

bool Rational::operator<=(const Rational &rational) const {
  return !(rational < *this);
}

bool Rational::operator>=(const Rational &rational) const {
  return !(*this < rational);
}

bool Rational::operator==(const Rational &rational) const {
  return numerator == rational.numerator &&
    denominator == rational.denominator;
}

bool Rational::operator!=(const Rational &rational) const {
  return !(rational == *this);
}

bool Rational::operator==(long long num) const {
  return denominator == 1 && num == numerator;
}

bool Rational::operator!=(long long num) const {
  return !(*this == num);
}

bool operator==(long long num, const Rational &rational) {
  return rational == num;
}

bool operator!=(long long num, const Rational &rational) {
  return rational != num;
}

std::string Rational::to_string() const {
  return "Rational: " + std::to_string(numerator) + " / " + std::to_string(denominator);
}

std::ostream &operator<<(std::ostream &out, const Rational &rational) {
  out << rational.to_string();
  return out;
}

float Rational::getFloat() const {
  return float(numerator) / float(denominator);
}





