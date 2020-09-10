#pragma once

#include "../math/Vector.hpp"

namespace Ocean {

  constexpr int RESOLUTION = 1024;
  constexpr float PATCH_SIZE = 30.0f;

  constexpr float WIND_SPEED = 3.5f;
  constexpr float GRAVITY = 9.81f;
  Vector2 WIND_DIRECTION = Normalize(Vector2(-1, -1));

} // namespace Ocean
