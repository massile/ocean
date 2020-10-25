#pragma once

#include "Vector.hpp"

namespace Ocean {

  struct Ray {
    Point3 origin;
    Direction3 direction;
    float intensity;

    Ray(const Point3 &origin, const Direction3 &direction, float intensity = 1.f)
        : origin(origin),
          direction(Normalize(direction)),
          intensity(intensity) {}
  };

} // namespace Ocean
