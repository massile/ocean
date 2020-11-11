#pragma once

#include "Image.hpp"
#include "../math/Ray.hpp"

namespace Ocean
{
  enum Material
  {
    SKY,
    WATER,
    BALL
  };

  struct Intersection
  {
    Material material;
    Point3 impactPoint;
    Direction3 normal;
  };

  Color horizonColor(1.71, 1.31, 0.83);
  Color skyColor(0.4, 0.75, 1);
  Color sunColor(1.5, 1, 0.6);
  Direction3 sunDirection = Normalize(Vector3(1.5, -1, 0.1));

  Color ComputeColor(const Ray &ray)
  {
    float mixWeight = sqrt(abs(ray.direction.z));
    Color sky = (1 - mixWeight) * horizonColor + mixWeight * skyColor;
    Color sun = 4 * sunColor * pow(fmax(Dot(sunDirection, ray.direction), 0), 1500);
    return sky + sun;
  }

  Direction3 SetPointOfView(const Point3 &pixel, const Point3 &eye, const Point3 &target)
  {
    Vector3 camZ = Normalize(target - eye);
    Vector3 camX = Cross(camZ, Vector3(0, 0, -1));
    Vector3 camY = Cross(camZ, camX);
    return 0.3 * pixel.x * camX + 0.3 * pixel.y * camY + pixel.z * camZ;
  }

  void Draw(Image &image)
  {
    Point3 eye(3.5, 3.5, 1.5);

    for (int x = 0; x < image.width; x++)
      for (int y = 0; y < image.height; y++)
      {
        // Normalise les coordonnées du pixel pour rendre le calcul indépendant des dimensions de l'image
        float xPixel = (float(x) / image.width - 0.5) * image.width / image.height;
        float yPixel = float(y) / image.height - 0.5;

        Point3 pixel(xPixel, yPixel, 1);
        // Changement de repère pour voir la scène sous différents angles
        Direction3 toPixel = SetPointOfView(pixel, eye, 0.f); 
        Ray ray(eye, toPixel);
        Color color = ComputeColor(ray);

        image(x, y) = 1.25 * Color(pow(log(color.x + 1), 1.3),
                                   pow(log(color.y + 1), 1.3),
                                   pow(log(color.z + 1), 1.3));
      }
  }
} // namespace Ocean
