#pragma once

#include "core/Math.h"
#include "material/Material.h"
#include "Intersectable.h"

namespace lm {

class Sphere : public Intersectable {
public:
    explicit Sphere(const Vec3f& origin, const Float radius, Material* material) :
        origin(origin), radius(radius), material(material) {}

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const {
        const auto l = ray.origin - origin;

        const Float a = lm::dot(ray.direction, ray.direction);
        const Float b = 2.0f * lm::dot(ray.direction, l);
        const Float c = lm::dot(l, l) - radius * radius;

        const auto roots = kc::math::solveQuadraticEquation(a, b, c);
        if (not roots) return {};

        auto [t0, t1] = *roots;
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0) return {};
        }
        if (not interval.contains(t0)) return {};

        auto intersectionPoint = ray.at(t0);

        const auto normal = normalize(intersectionPoint - origin);
        bool isFrontFace  = dot(ray.direction, normal) < 0;
        return Intersection(t0, intersectionPoint, isFrontFace, normal, material);
    }

    const Vec3f origin;
    const Float radius;
    Material* material;
};

}  // namespace lm