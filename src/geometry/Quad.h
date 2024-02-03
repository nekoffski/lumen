#pragma once

#include "core/Math.h"
#include "material/Material.h"
#include "Intersectable.h"

namespace lm {

class Quad : public Intersectable {
public:
    explicit Quad(
      const Vec3f& origin, const Vec3f& u, const Vec3f& v, Material* material
    ) :
        origin(origin),
        u(u), v(v), material(material), normal(normalize(cross(u, v))),
        d(dot(normal, origin)) {
        auto n = cross(u, v);
        w      = n / dot(n, n);
    }

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const {
        auto denom = dot(normal, ray.direction);

        if (std::fabs(denom) < 1e-8)  // parallel hit
            return {};

        auto t = (d - dot(normal, ray.origin)) / denom;
        if (not interval.contains(t)) return {};

        // Determine the hit point lies within the planar shape using its plane
        // coordinates.
        auto intersection        = ray.at(t);
        vec3 planar_hitpt_vector = intersection - origin;
        auto alpha               = dot(w, cross(planar_hitpt_vector, v));
        auto beta                = dot(w, cross(u, planar_hitpt_vector));

        if (not isInterior(alpha, beta)) return {};

        bool isFrontFace = dot(ray.direction, normal) < 0;
        return Intersection(t, intersection, isFrontFace, normal, material);
    }

    bool isInterior(Float a, Float b) const {
        // Given the hit point in plane coordinates, return false if it is outside
        // the primitive, otherwise set the hit record UV coordinates and return
        // true.
        return !((a < 0) || (1 < a) || (b < 0) || (1 < b));
    }

    const Vec3f origin;
    const Vec3f u;
    const Vec3f v;
    const Vec3f normal;
    const Float d;
    Vec3f w;
    Material* material;
};

}  // namespace lm
