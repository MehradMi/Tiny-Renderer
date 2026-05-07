#include "Vec2D.h"

float Vec2D::length(Vec2D v) {
  float _length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
  return _length;
}

Vec2D Vec2D::add(Vec2D a, Vec2D b) {
  Vec2D _result {
    a.x + b.x,
    a.y + b.y
  };

  return _result;
}

Vec2D Vec2D::sub(Vec2D a, Vec2D b) {
  Vec2D _result {
    a.x - b.x,
    a.y - b.y
  };

  return _result;
}

Vec2D Vec2D::mul(Vec2D a, float s) {
  Vec2D _result {
    a.x * s,
    a.y * s,
  };

  return _result;
}

Vec2D Vec2D::div(Vec2D a, float s) {
  if (s != 0.0f) {
    Vec2D _result {
      a.x / s,
      a.y / s,
    };

    return _result;
  }

  std::cerr << "ERROR::VEC2D::DIVISION_BY_ZERO" << std::endl;
  return a;
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
