#pragma once

#include "Image.hpp"
#include "../math/Ray.hpp"

namespace Ocean {
  Color ComputeColor(const Ray &ray) {
    return Color(1, 1, 0);
  }

  void Draw(Image &image) {
    Point3 eye(0, 0, -2);

    for (int x = 0; x < image.width; x++)
      for (int y = 0; y < image.height; y++) {
        // Normalise les coordonnées du pixel pour rendre le calcul indépendant des dimensions de l'image
        float xPixel = (float(x) / image.width - 0.5) * image.width / image.height;
        float yPixel = float(y) / image.height - 0.5;

        Point3 pixel(xPixel, yPixel, 0);
        Ray ray(pixel, pixel - eye);
        image(x, y) = ComputeColor(ray);
      }
  }
} // namespace Ocean
