#include "Vec3D.h"

void Vec3D::Rotate(Axis a, float angle) {
  float _x = x, _y = y, _z = z;
  switch(a) {
    case (Axis::X): 
      {
        y = _y * cos(angle) - _z * sin(angle);
        z = _z * cos(angle) + _y * sin(angle);
        return;
      }
    case (Axis::Y):
      {
        x = _x * cos(angle) - _z * sin(angle);
        z = _z * cos(angle) + _x * sin(angle);
        return;
      }
    case (Axis::Z):
      {
        x = _x * cos(angle) - _y * sin(angle);
        y = _y * cos(angle) + _x * sin(angle);
        return;
      }
    default:
      return;
  };
}

void Vec3D::StrangeRotate(Axis a, float angle) {
  switch(a) {
    case (Axis::X): 
      {
        y = y * cos(angle) - z * sin(angle);
        z = z * cos(angle) + y * sin(angle);
        return;
      }
    case (Axis::Y):
      {
        x = x * cos(angle) - z * sin(angle);
        z = z * cos(angle) + x * sin(angle);
        return;
      }
    case (Axis::Z):
      {
        x = x * cos(angle) - y * sin(angle);
        y = y * cos(angle) + x * sin(angle);
        return;
      }
    default:
      return;
  };
}

Vec3D Vec3D::operator+(const Vec3D& rhs) const {
  Vec3D _result {
    this->x + rhs.x,
    this->y + rhs.y,
    this->z + rhs.z
  };
  return _result;
}

Vec3D Vec3D::operator-(const Vec3D& rhs) const {
  Vec3D _result {
    this->x - rhs.x,
    this->y - rhs.y,
    this->z - rhs.z
  };
  return _result;
}

Vec3D Vec3D::operator*(const float& rhs) const {
  Vec3D _result {
    this->x * rhs,
    this->y * rhs,
    this->z * rhs
  };
  return _result;
}

Vec3D Vec3D::operator/(const float& rhs) const {
  if (rhs != 0.0f) {
    Vec3D _result {
      this->x / rhs,
      this->y / rhs,
      this->z / rhs,
    };
    return _result;
  }

  std::cerr << "ERROR::VEC2D::DIVISION_BY_ZERO" << std::endl;
  return *this;
}

float Vec3D::length(Vec3D v) {
  float _length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2)); 
  return _length;
}

Vec3D Vec3D::cross(Vec3D a, Vec3D b) {
  Vec3D _result {
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x,
  };

  return _result;
}

float Vec3D::dot(Vec3D a, Vec3D b) {
  float _result { a.x * b.x + a.y * b.y + a.z * b.z };
  return _result;
}

void Vec3D::normalize(Vec3D& v) {
  float _length { Vec3D::length(v) };
  v.x /= _length;
  v.y /= _length;
  v.z /= _length;
}
