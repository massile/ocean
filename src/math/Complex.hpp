#pragma once

#include <math.h>

namespace Ocean {

  struct Complex {
    float real;
    float imag;

    Complex() : real(0), imag(0) {}
    Complex(float real, float imag) : real(real), imag(imag) {}

    inline Complex operator+(const Complex &c) const {
      return Complex(real + c.real,
                     imag + c.imag);
    }

    inline Complex operator-(const Complex &c) const {
      return Complex(real - c.real,
                     imag - c.imag);
    }

    inline Complex operator*(float a) const {
      return Complex(real * a,
                     imag * a);
    }

    inline Complex operator/(float a) const {
      return Complex(real / a, imag / a);
    }

    inline Complex operator*(const Complex &c) const {
      return Complex(real * c.real - imag * c.imag,
                     real * c.imag + c.real * imag);
    }
  };

  inline Complex operator*(float a, const Complex &c) {
    return Complex(c.real * a, c.imag * a);
  }

  inline Complex Conjugate(const Complex &c) {
    return Complex(c.real, -c.imag);
  }

  inline Complex ExpI(float theta) {
    return Complex(cosf(theta), sinf(theta));
  }
} // namespace Ocean
