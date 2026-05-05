#include "vector.h"

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

float vec_length(Vec2D v) {
  float _length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
  return _length;
}

float vec_length(Vec3D v) {
  float _length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2)); 
  return _length;
}

Vec2D vec_add(Vec2D a, Vec2D b) {
  Vec2D _result {
    a.x + b.x,
    a.y + b.y
  };

  return _result;
}

Vec3D vec_add(Vec3D a, Vec3D b) {
  Vec3D _result {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z
  };

  return _result;
}

Vec2D vec_sub(Vec2D a, Vec2D b) {
  Vec2D _result {
    a.x - b.x,
    a.y - b.y
  };

  return _result;
}

Vec3D vec_sub(Vec3D a, Vec3D b) {
  Vec3D _result {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
  };

  return _result;
}


Vec2D vec_smul(Vec2D a, float s) {
  Vec2D _result {
    a.x * s,
    a.y * s,
  };

  return _result;
}

Vec3D vec_smul(Vec3D a, float s) {
  Vec3D _result {
    a.x * s,
    a.y * s,
    a.z * s
  };

  return _result;
}

Vec2D vec_sdiv(Vec2D a, float s) {
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
Vec3D vec_sdiv(Vec3D a, float s) {
  if (s != 0.0f) {
    Vec3D _result {
      a.x / s,
      a.y / s,
      a.z / s,
    };

    return _result;
  }

  std::cerr << "ERROR::VEC2D::DIVISION_BY_ZERO" << std::endl;
  return a;
}

Vec3D vec_cross(Vec3D a, Vec3D b) {
  Vec3D _result {
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x,
  };

  return _result;
}

float vec_dot(Vec2D a, Vec2D b) {
  float _result { a.x * b.x + a.y * b.y };
  return _result;
}

float vec_dot(Vec3D a, Vec3D b) {
  float _result { a.x * b.x + a.y * b.y + a.z * b.z };
  return _result;
}

void vec_normalize(Vec2D& v) {
  float _length {vec_length(v)};
  v.x /= _length;
  v.y /= _length;
}
void vec_normalize(Vec3D& v) {
  float _length {vec_length(v)};
  v.x /= _length;
  v.y /= _length;
  v.z /= _length;
}
