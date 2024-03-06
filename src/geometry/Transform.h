#pragma once

#include <vector>
#include <memory>

#include "core/Ray.h"
#include "core/Math.h"

#include "AABB.h"
#include "Intersectable.h"

namespace lm {

struct Transform {
    virtual Ray transformRay(const Ray&) const                            = 0;
    virtual AABB transformBoundingBox(const AABB&) const                  = 0;
    virtual Intersection transformIntersection(const Intersection&) const = 0;
};

class TransformChain : public Transform {
public:
    template <typename T, typename... Args> Transform* add(Args&&... args) {
        m_transforms.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return m_transforms.back().get();
    }

    Ray transformRay(const Ray& r) const override {
        auto ray = r;
        for (auto& transform : m_transforms) ray = transform->transformRay(ray);
        return ray;
    }

    AABB transformBoundingBox(const AABB& a) const override {
        auto aabb = a;
        for (auto& transform : m_transforms)
            aabb = transform->transformBoundingBox(aabb);
        return aabb;
    }

    Intersection transformIntersection(const Intersection& i) const override {
        auto intersection = i;
        for (auto& transform : m_transforms)
            intersection = transform->transformIntersection(intersection);
        return intersection;
    }

private:
    std::vector<std::unique_ptr<Transform>> m_transforms;
};

class Translate : public Transform {
public:
    explicit Translate(const Vec3f& offset) : m_offset(offset) {}

    Ray transformRay(const Ray& r) const override {
        return Ray(r.origin - m_offset, r.direction);
    }

    AABB transformBoundingBox(const AABB& a) const override {
        return AABB(a.getMin() - m_offset, a.getMax() - m_offset);
    }

    Intersection transformIntersection(const Intersection& i) const override {
        auto intersection = i;
        intersection.intersectionPoint += m_offset;
        return intersection;
    }

private:
    Vec3f m_offset;
};

class Rotation : public Transform {
public:
    explicit Rotation(const Vec3f& angles) : m_angles(angles) {
        m_rotation =
          rotate(radians(m_angles.x), Vec3f{ 1.0f, 0.0f, 0.0f })
          * rotate(radians(m_angles.y), Vec3f{ 0.0f, 1.0f, 0.0f })
          * rotate(radians(m_angles.z), Vec3f{ 0.0f, 0.0f, 1.0f });
        m_rotationInverse = inverse(m_rotation);
    }

    Ray transformRay(const Ray& r) const override {
        auto origin = Vec3f{
            m_rotation * Vec4f{r.origin, 1.0f}
        };
        auto direction = Vec3f{
            m_rotation * Vec4f{r.direction, 1.0f}
        };

        return Ray(origin, direction);
    }

    AABB transformBoundingBox(const AABB& a) const override {
        return AABB(a.getMin() - m_angles, a.getMax() - m_angles);
    }

    Intersection transformIntersection(const Intersection& i) const override {
        auto intersection              = i;
        intersection.intersectionPoint = Vec3f{
            m_rotationInverse * Vec4f{intersection.intersectionPoint, 1.0f}
        };
        intersection.normal = Vec3f{
            m_rotationInverse * Vec4f{intersection.normal, 1.0f}
        };
        return intersection;
    }

private:
    Vec3f m_angles;

    Mat4f m_rotation;
    Mat4f m_rotationInverse;
};

}  // namespace lm
