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
