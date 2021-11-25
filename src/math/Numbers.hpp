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

  int Floor(float x) {
    return x < 0 ? int(x) - 1 : int(x);
  }

  float Fract(float x) {
    return x - Floor(x);
  }

  float Mod(float x, float y) {
    return x - y * Floor(x / y);
  }

  template <typename T>
  T Mix(T x, T y, float a) {
    return (1.f - a) * x + a * y;
  }

  template <typename T>
  T BilinearInterpolation(float x, float y, int width, int height, T *values) {
    int xi1 = Mod(x, width - 1);
    int yi1 = Mod(y, height - 1);
    int xi2 = Mod(x + 1, width - 1);
    int yi2 = Mod(y + 1, height - 1);

    T topLeft = values[yi1 + xi1 * width];
    T topRight = values[yi1 + xi2 * width];
    T bottomLeft = values[yi2 + xi1 * width];
    T bottomRight = values[yi2 + xi2 * width];

    float xf = Fract(x);
    T top = Mix(topLeft, topRight, xf);
    T bottom = Mix(bottomLeft, bottomRight, xf);

    return Mix(top, bottom, Fract(y));
  }

} // namespace Ocean
