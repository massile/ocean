#pragma once

namespace Ocean {

  float Random() {
    static unsigned int randomState = 0x36dc64af;
    randomState = randomState ^ (randomState << 13u);
    randomState = randomState ^ (randomState >> 17u);
    randomState = randomState ^ (randomState << 5u);
    randomState *= 1685821657u;
    unsigned int intermediate = ((randomState & 0x007FFFFFu) | 0x3F800000u);
    return *((float *)(&intermediate)) - 1.0f;
  }

  float RandomGaussian() {
    float a = 0.f;
    for (int i = 0; i < 12; i++)
      a += Random();
    return a - 6.f;
  }
} // namespace Ocean
