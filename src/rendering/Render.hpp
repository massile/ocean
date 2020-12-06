#pragma once

#include "Constants.hpp"
#include "ImpactPoint.hpp"
#include "../math/Ray.hpp"

namespace Ocean {
  Color SkyColor(const Direction3 &dir) {
    float mixWeight = sqrt(fabs(dir.z));
    Color sky = (1 - mixWeight) * HORIZON_COLOR + mixWeight * SKY_COLOR;
    Color sun = 4 * SUN_COLOR * pow(fmax(Dot(SUN_DIRECTION, dir), 0), 1500);
    return sky + sun;
  }

  Color ComputeColor(const Ray &ray) {
    Intersection inter = FindIntersectionForRay(ray);
    Color skyColor = ray.intensity * SkyColor(ray.direction);

    if (inter.material == SKY) {
      return skyColor;
    }

    Point3 newOrigin = inter.impactPoint + 0.01f * inter.normal;
    Direction3 newDirection = Reflect(ray.direction, inter.normal);

    float frensel = fabs(Dot(ray.direction, inter.normal));
    Color newIntensity = (1.f - 0.9f * frensel) * ray.intensity;
    Ray newRay(newOrigin, newDirection, newIntensity);

    float fog = (1.0f - fmax(0.f, powf(1 - Length(ray.origin - inter.impactPoint) / FOG_DISTANCE, FOG_INTENSITY)));
    return fog * skyColor + ComputeColor(newRay);
  }

  Direction3 SetPointOfView(const Point3 &pixel, const Point3 &eye, const Point3 &target) {
    Vector3 camZ = Normalize(target - eye);
    Vector3 camX = Cross(camZ, Vector3(0, 0, -1));
    Vector3 camY = Cross(camZ, camX);
    return 0.3 * pixel.x * camX + 0.3 * pixel.y * camY + pixel.z * camZ;
  }

  Color GeneratePixelColor(float xPixel, float yPixel) {
    Point3 eye = EYE_POSITION + EYE_APERTURE_SIZE * Normalize(Vector3(Random(), Random(), Random()));
    Direction3 toPixel = SetPointOfView(Point3(xPixel, yPixel, 1), eye, Point3(0, 0, 0.2f));
    Ray ray(eye, toPixel);
    return ComputeColor(ray);
  }

  void Draw(Image &image) {
    for (int x = 0; x < image.width; x++)
      for (int y = 0; y < image.height; y++) {
        // Normalise les coordonnées du pixel pour rendre le calcul indépendant des dimensions de l'image
        float xPixel = (float(x) / image.width - 0.5) * image.width / image.height;
        float yPixel = float(y) / image.height - 0.5;

        Color totalColor;
        for (int i = 0; i < 10; i++)
          totalColor = totalColor + GeneratePixelColor(xPixel, yPixel);
        totalColor = totalColor / 10;

        Color color = (1.0f - 0.58f * (xPixel * xPixel + yPixel * yPixel)) * totalColor;
        image(x, y) = 1.25 * Color(pow(log(color.x + 1), 1.3),
                                   pow(log(color.y + 1), 1.3),
                                   pow(log(color.z + 1), 1.3));
      }
  }
} // namespace Ocean
