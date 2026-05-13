#include "Vec2D.h"

float Vec2D::length(Vec2D v) {
  float _length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
  return _length;
}

Vec2D Vec2D::operator+(const Vec2D& rhs) const {
  Vec2D _result {
    x + rhs.x,
    y + rhs.y
  };
  return _result;
}

Vec2D Vec2D::operator-(const Vec2D& rhs) const {
  Vec2D _result {
    x - rhs.x,
    y - rhs.y
  };
  return _result;
}

Vec2D Vec2D::operator*(const float& rhs) const {
  Vec2D _result {
    x * rhs,
    y * rhs,
  };
  return _result;
}

Vec2D Vec2D::operator/(const float& rhs) const {
  if (rhs != 0.0f) {
    Vec2D _result {
      x / rhs,
      y / rhs
    };
    return _result;
  }

  std::cerr << "ERROR::VEC2D::DIVISION_BY_ZERO" << std::endl;
  return *this;
}

float Vec2D::dot(Vec2D a, Vec2D b) {
  float _result { a.x * b.x + a.y * b.y };
  return _result;
}

void Vec2D::normalize(Vec2D& v) {
  float _length { Vec2D::length(v) };
  v.x /= _length;
  v.y /= _length;
}
