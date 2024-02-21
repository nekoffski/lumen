#pragma once

#include "Intersectable.h"
#include "IntersectableCollection.h"

#include "AABB.h"
#include "Quad.h"

namespace lm {

class Box : public Intersectable {
public:
    explicit Box(const Vec3f& min, const Vec3f& max, Material* material) :
        m_boundingBox(min, max) {
        m_faces.reserve(6);

        const auto dx = Vec3f{ std::fabs(max.x - min.x), 0.0f, 0.0f };
        const auto dy = Vec3f{ 0.0f, std::fabs(max.y - min.y), 0.0f };
        const auto dz = Vec3f{ 0.0f, 0.0f, std::fabs(max.z - min.z) };

        // front
        m_faces.emplace_back(Vec3f{ max.x, min.y, min.z }, -dx, dy, material);
        // right
        m_faces.emplace_back(min, dz, dy, material);
        // back
        m_faces.emplace_back(Vec3f{ min.x, min.y, max.z }, dx, dy, material);
        // // left
        m_faces.emplace_back(Vec3f{ max.x, min.y, max.z }, -dz, dy, material);
        // top
        m_faces.emplace_back(max, -dz, -dx, material);
        // bottom
        m_faces.emplace_back(min, dx, dz, material);

        for (auto& face : m_faces) m_composite.add(&face);
        m_composite.buildBoundingVolume();
    }

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const override {
        return m_composite.intersect(ray, interval);
    }

    const BoundingVolume* getBoundingVolume() const override {
        return &m_boundingBox;
    }

private:
    Vec3f m_min;
    Vec3f m_max;

    AABB m_boundingBox;

    std::vector<Quad> m_faces;
    IntersectableCollection m_composite;
};

}  // namespace lm