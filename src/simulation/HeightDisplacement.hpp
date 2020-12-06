#pragma once

#include "Constants.hpp"
#include <math.h>
#include "../math/Numbers.hpp"
#include "../math/Complex.hpp"
#include "../math/Fourier.hpp"

namespace Ocean {
  Complex *spectrum0 = new Complex[RESOLUTION * RESOLUTION];
  Complex *spectrum = new Complex[RESOLUTION * RESOLUTION];

  Complex *choppinesses = new Complex[RESOLUTION * RESOLUTION];
  Complex *choppinessDisplacements = new Complex[RESOLUTION * RESOLUTION];

  float *heights = new float[RESOLUTION * RESOLUTION];
  float *angularSpeeds = new float[RESOLUTION * RESOLUTION];

  template <typename T>
  T GetRemappedValues(float x, float y, T *values) {
    return 0.000048F * BilinearInterpolation(100.f * x, 100.f * y, RESOLUTION, RESOLUTION, values);
  }

  Vector2 GetChoppinessDisplacement(float x, float y) {
    Complex displacement = GetRemappedValues(x, y, choppinessDisplacements);
    return CHOPPINESS * Vector2(displacement.real, displacement.imag);
  }

  float GetHeight(float x, float y) {
    Vector2 horizontalDisplacement = GetChoppinessDisplacement(x, y);
    x -= horizontalDisplacement.x;
    y -= horizontalDisplacement.y;
    return GetRemappedValues(x, y, heights);
  }

  float PhillipsSpectrumCoefs(const Vector2 &k) {
    float L = WIND_SPEED * WIND_SPEED / GRAVITY;
    float l = L / 300.0f;

    float kDotw = Dot(k, WIND_DIRECTION);
    float k2 = Dot(k, k);
    if (k2 < 0.000001f)
      return 0;

    float phillips = expf(-1.f / (k2 * L * L)) / (k2 * k2 * k2) * (kDotw * kDotw);
    // La vague se déplace dans le sens contraire du vent
    if (kDotw < 0)
      phillips *= 0.01f;

    return phillips * expf(-k2 * l * l);
  }

  void GenerateSpectra() {
    for (int i = 0; i < RESOLUTION; i++)
      for (int j = 0; j < RESOLUTION; j++) {
        Vector2 k = M_PI / PATCH_SIZE * Vector2(RESOLUTION - 2 * i, RESOLUTION - 2 * j);
        float p = sqrtf(PhillipsSpectrumCoefs(k) / 2);

        int index = i * RESOLUTION + j;
        spectrum0[index] = Complex(RandomGaussian() * p, RandomGaussian() * p);
        angularSpeeds[index] = sqrt(GRAVITY * Length(k));
      }
  }

  void UpdateHeights(float t) {
    for (int x = 0; x < RESOLUTION; x++) {
      for (int y = 0; y < RESOLUTION; y++) {
        int i = y + x * RESOLUTION;
        float wt = angularSpeeds[i] * t;
        Complex h = spectrum0[i];
        Complex h1;
        if (y == 0 && x == 0)
          h1 = spectrum0[RESOLUTION * RESOLUTION - 1];
        else if (y == 0)
          h1 = spectrum0[RESOLUTION - 1 + (RESOLUTION - x) * RESOLUTION];
        else if (x == 0)
          h1 = spectrum0[RESOLUTION - y + (RESOLUTION - x - 1) * RESOLUTION];
        else
          h1 = spectrum0[(RESOLUTION - y) + (RESOLUTION - x) * RESOLUTION];

        Vector2 k = Normalize(Vector2(RESOLUTION * .5f - x, RESOLUTION * .5f - y));
        Complex spec = h * ExpI(wt) + Conjugate(h1) * ExpI(-wt);
        spectrum[i] = spec;
        choppinesses[i] = Complex(k.y, -k.x) * spec;
      }
    }

    InverseFourierTransform2D(RESOLUTION, spectrum);
    InverseFourierTransform2D(RESOLUTION, choppinesses);

    for (int i = 0; i < RESOLUTION; i++)
      for (int j = 0; j < RESOLUTION; j++) {
        float sign = ((i + j) % 2) ? -1 : 1;
        int index = i * RESOLUTION + j;
        heights[index] = sign * spectrum[index].real;
        choppinessDisplacements[index] = sign * choppinesses[index];
      }
  }

} // namespace Ocean
