#pragma once

#include "../math/Ray.hpp"

namespace Ocean {
  enum Material {
    SKY,
    WATER,
    BALL
  };

  struct Intersection {
    Material material;
    Point3 impactPoint;
    Direction3 normal;
  };

  float MeasureDistanceToBall(Point3 p) {
    Point3 center(0, 0, 0.6f);
    return Length(p - center) - 0.7f;
  }

  float MeasureDistanceToPlane(Point3 p) {
    float height = Ocean::GetHeight(p.x, p.y);
    return p.z - height;
  }

  Vector3 GradientBall(const Point3 &p) {
    Direction3 dx(0.001f, 0, 0);
    Direction3 dy(0, 0.001f, 0);
    Direction3 dz(0, 0, 0.001f);

    return Normalize(Vector3(
        MeasureDistanceToBall(p + dx) - MeasureDistanceToBall(p - dx),
        MeasureDistanceToBall(p + dy) - MeasureDistanceToBall(p - dy),
        MeasureDistanceToBall(p + dz) - MeasureDistanceToBall(p - dz)));
  }

  Vector3 GradientPlane(const Point3 &p) {
    Direction3 dx(0.001f, 0, 0);
    Direction3 dy(0, 0.001f, 0);
    Direction3 dz(0, 0, 0.001f);

    return Normalize(Vector3(
        MeasureDistanceToPlane(p + dx) - MeasureDistanceToPlane(p - dx),
        MeasureDistanceToPlane(p + dy) - MeasureDistanceToPlane(p - dy),
        MeasureDistanceToPlane(p + dz) - MeasureDistanceToPlane(p - dz)));
  }

  Intersection FindIntersectionForRay(const Ray &ray) {
    float distanceFromEye = 0;
    for (int i = 0; i < 255; i++) {
      Point3 impactPoint = ray.PointAt(distanceFromEye);
      float measuredDistanceToBall = MeasureDistanceToBall(impactPoint);
      float measuredDistanceToPlane = MeasureDistanceToPlane(impactPoint);
      distanceFromEye += fmin(measuredDistanceToBall, measuredDistanceToPlane);

      if (measuredDistanceToBall < 0.001f) {
        return {
            .material = BALL,
            .impactPoint = impactPoint,
            .normal = GradientBall(impactPoint),
        };
      }

      if (measuredDistanceToPlane < 0.001f) {
        return {
            .material = WATER,
            .impactPoint = impactPoint,
            .normal = GradientPlane(impactPoint),
        };
      }

      if (distanceFromEye > 1000.f)
        return {.material = SKY};
    }
    return {.material = SKY};
  }

} // namespace Ocean
