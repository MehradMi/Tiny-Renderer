#ifndef VECTOR_H
#define VECTOR_H

class Vec2D {
  private:
    float m_x;
    float m_y;

  public:
    Vec2D(float x, float y);
};

class Vec3D {
  private:
    float m_x;
    float m_y;
    float m_z;

  public:
    Vec3D(float x, float y, float z);
};

#endif
