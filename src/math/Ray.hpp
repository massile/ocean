#pragma once

#include "Vector.hpp"

namespace Ocean {

  struct Ray {
    Point3 origin;
    Direction3 direction;
    Color intensity;

    Ray(const Point3 &origin, const Direction3 &direction, Color intensity = 1.f)
        : origin(origin),
          direction(Normalize(direction)),
          intensity(intensity) {}

    inline Point3 PointAt(float distanceFromOrigin) const {
      return origin + distanceFromOrigin * direction;
    }
  };

} // namespace Ocean
