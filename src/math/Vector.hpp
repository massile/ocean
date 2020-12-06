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

  struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x) : x(x), y(x), z(x) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    inline Vector3 operator+(const Vector3 &v) const {
      return Vector3(x + v.x, y + v.y, z + v.z);
    }

    inline Vector3 operator-(const Vector3 &v) const {
      return Vector3(x - v.x, y - v.y, z - v.z);
    }

    inline Vector3 operator*(const Vector3 &v) const {
      return Vector3(x * v.x, y * v.y, z * v.z);
    }

    inline Vector3 operator*(float a) const {
      return Vector3(a * x, a * y, a * z);
    }

    inline Vector3 operator/(float a) const {
      return Vector3(x / a, y / a, z / a);
    }
  };

  inline Vector3 operator*(float a, const Vector3 &v) {
    return Vector3(a * v.x, a * v.y, a * v.z);
  }

  inline float Dot(const Vector3 &u, const Vector3 &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
  }

  inline float LengthSquared(const Vector3 &u) {
    return Dot(u, u);
  }

  inline float Length(const Vector3 &u) {
    return sqrtf(LengthSquared(u));
  }

  inline Vector3 Normalize(const Vector3 &u) {
    float l = Length(u);
    if (l < 0.00001f)
      return 0.f;
    return u / l;
  }

  inline Vector3 Cross(const Vector3 &u, const Vector3 &v) {
    return Vector3(u.y * v.z - u.z * v.y,
                   u.z * v.x - u.x * v.z,
                   u.x * v.y - u.y * v.x);
  }

  inline Vector3 Reflect(const Vector3 &u, const Vector3 &axis) {
    return u - 2 * Dot(u, axis) * axis;
  }

  using Point3 = Vector3;
  using Direction3 = Vector3;
} // namespace Ocean
