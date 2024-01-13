#pragma once

#include "core/Math.h"
#include "Intersectable.h"

namespace lm {

class Sphere : public Intersectable {
public:
    explicit Sphere(const Vec3f& origin, const Float radius, const Vec3f& color) :
        origin(origin), radius(radius), color(color) {}

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const {
        const auto l = ray.origin - origin;

        const float a = lm::dot(ray.direction, ray.direction);
        const float b = 2.0f * lm::dot(ray.direction, l);
        const float c = lm::dot(l, l) - radius * radius;

        const auto roots = kc::math::solveQuadraticEquation(a, b, c);
        if (not roots) return {};

        auto [t0, t1] = *roots;
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0) return {};
        }
        if (not interval.inBetween(t0)) return {};

        return Intersection{
            .t = t0, .intersectionPoint = ray.at(t0), .color = color
        };
    }

    const Vec3f origin;
    const Float radius;
    const Vec3f color;
};

}  // namespace lm