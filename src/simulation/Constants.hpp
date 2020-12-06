#pragma once

#include "../math/Vector.hpp"

namespace Ocean {

  constexpr int RESOLUTION = 1024;
  constexpr float PATCH_SIZE = 256.0f;

  constexpr float WIND_SPEED = 4.5f;
  constexpr float GRAVITY = 9.81f;
  constexpr float CHOPPINESS = 1.2f;
  Vector2 WIND_DIRECTION = Normalize(Vector2(-1, -1));

} // namespace Ocean
