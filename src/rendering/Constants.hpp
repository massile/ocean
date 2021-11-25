#pragma once

#include "Image.hpp"

namespace Ocean {
  Color HORIZON_COLOR(1.71, 1.31, 0.83);
  Color SKY_COLOR(0.4, 0.75, 1);
  Color SUN_COLOR(1.5, 1, 0.6);
  Direction3 SUN_DIRECTION = Normalize(Vector3(-1.5, -1.2, 0.1));
  int NUM_SAMPLES = 3; // Increase to reduce noise on the image (but has a big impact on performance)

  constexpr float FOG_INTENSITY = 1.2f;
  constexpr float FOG_DISTANCE = 100.f;

  constexpr float EYE_APERTURE_SIZE = 0.15f;
  Vector3 EYE_POSITION(7.5, 7.5, 5.f);
} // namespace Ocean
