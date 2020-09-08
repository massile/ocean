#pragma once

#include <math.h>

namespace Ocean {
  struct Vector2 {
    float x;
    float y;

    Vector2() : x(0), y(0) {}
    Vector2(float x) : x(x), y(x) {}
    Vector2(float x, float y) : x(x), y(y) {}

    inline Vector2 operator+(const Vector2 &v) const {
      return Vector2(x + v.x, y + v.y);
    }

    inline Vector2 operator-(const Vector2 &v) const {
      return Vector2(x - v.x, y - v.y);
    }

    inline Vector2 operator*(float a) const {
      return Vector2(a * x, a * y);
    }

    inline Vector2 operator/(float a) const {
      return Vector2(x / a, y / a);
    }
  };

  inline Vector2 operator*(float a, const Vector2 &v) {
    return Vector2(a * v.x, a * v.y);
  }

  inline float Dot(const Vector2 &u, const Vector2 &v) {
    return u.x * v.x + u.y * v.y;
  }

  inline float LengthSquared(const Vector2 &u) {
    return Dot(u, u);
  }

  inline float Length(const Vector2 &u) {
    return sqrtf(LengthSquared(u));
  }

  inline Vector2 Normalize(const Vector2 &u) {
    float l = Length(u);
    if (l < 0.00001f)
      return 0.f;
    return u / l;
  }
} // namespace Ocean
