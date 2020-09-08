#pragma once

#include "Complex.hpp"

namespace Ocean {
  void CooleyTukey(int N, int s, int q, int d, Complex *x) {
    int m = N / 2;
    if (N > 1) {
      for (int p = 0; p < m; p++) {
        Complex wp = ExpI(-p * 2 * M_PI / N);
        Complex a = x[q + p + 0];
        Complex b = x[q + p + m];
        x[q + p + 0] = a + b;
        x[q + p + m] = (a - b) * wp;
      }
      CooleyTukey(N / 2, 2 * s, q + 0, d + 0, x);
      CooleyTukey(N / 2, 2 * s, q + m, d + s, x);
    } else if (q > d) {
      Complex tmp = x[q];
      x[q] = x[d];
      x[d] = tmp;
    }
  }

  void FourierTransform(int N, Complex *x) {
    CooleyTukey(N, 1, 0, 0, x);
  }

  void InverseFourierTransform(int N, Complex* x) {
    for (int p = 0; p < N; p++)
      x[p] = Conjugate(x[p]);
    FourierTransform(N, x);    
    for (int p = 0; p < N; p++)
      x[p] = Conjugate(x[p]);
  }

  void InverseFourierTransform2D(int N, Complex* c) {
    Complex* rows = new Complex[N];
    for (int y = 0; y < N; y++) {
      for (int x = 0; x < N; x++)
        rows[x] = c[y + x*N];
      InverseFourierTransform(N, rows);
      for (int x = 0; x < N; x++)
        c[y + x*N] = rows[x];
    }
    
    Complex* columns = new Complex[N];
    for (int x = 0; x < N; x++) {
      for (int y = 0; y < N; y++)
        columns[y] = c[y + x*N];
      InverseFourierTransform(N, columns);
      for (int y = 0; y < N; y++)
        c[y + x*N] = columns[y];
    }
  }

} // namespace Ocean
