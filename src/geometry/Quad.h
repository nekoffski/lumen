#pragma once

#include "core/Math.h"
#include "material/Material.h"
#include "Intersectable.h"
#include "AABB.h"

namespace lm {

class Quad : public Intersectable {
public:
    explicit Quad(
      const Vec3f& origin, const Vec3f& u, const Vec3f& v, Material* material
    ) :
        origin(origin),
        u(u), v(v), material(material), normal(normalize(cross(u, v))),
        d(dot(normal, origin)), m_boundingBox(origin, origin + u + v) {
        auto n = cross(u, v);
        w      = n / dot(n, n);
    }

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const {
        static constexpr Float delta = 1e-8f;
        const auto denominator       = dot(normal, ray.direction);

        if (std::fabs(denominator) < delta) return {};  // parallel hit

        auto hitInterval = (d - dot(normal, ray.origin)) / denominator;

        if (not interval.contains(hitInterval)) return {};

        auto hitPoint = ray.at(hitInterval);

        const auto alfa = dot(w, cross(hitPoint - origin, v));
        const auto beta = dot(w, cross(u, hitPoint - origin));

        static Interval unitInterval{ 0.0f, 1.0f };

        if (not unitInterval.contains(alfa) || not unitInterval.contains(beta))
            return {};

        bool frontFace = dot(ray.direction, normal) < 0;
        if (not frontFace) return {};

        return Intersection{ hitInterval, hitPoint, frontFace, normal, material };
    }

    const BoundingVolume* getBoundingVolume() const { return &m_boundingBox; }

    const Vec3f origin;
    const Vec3f u;
    const Vec3f v;
    const Vec3f normal;
    const Float d;
    Vec3f w;
    Material* material;
    AABB m_boundingBox;
};

}  // namespace lm
