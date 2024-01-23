#include "Intersectable.h"

namespace lm {

Intersection::Intersection(
  Float t, const Vec3f& intersectionPoint, const Vec3f& normal, Material* material
) :
    t(t),
    intersectionPoint(intersectionPoint), normal(normal), m_material(material) {}

Vec3f Intersection::getColor() const {
    return m_material->getTexture()->getColor({ 0.0f, 0.0f });
}

std::optional<ScatterRecord> Intersection::scatter(const Ray& ray) const {
    return m_material->scatter(ray, normal, intersectionPoint);
}

}  // namespace lm
