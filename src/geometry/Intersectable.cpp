#include "Intersectable.h"

namespace lm {

Intersection::Intersection(
  Float t, const Vec3f& intersectionPoint, bool isFrontFace, const Vec3f& normal,
  Material* material
) :
    t(t),
    intersectionPoint(intersectionPoint), isFrontFace(isFrontFace),
    normal(isFrontFace ? normal : -normal), m_material(material) {
    this->intersectionPoint += 0.0001f * this->normal;
}

Vec3f Intersection::getColor() const {
    return m_material->getTexture()->getColor({ 0.0f, 0.0f });
}

// TODO: add uv
Vec3f Intersection::getEmittedColor() const {
    return m_material->getEmittedColor({ 0.0f, 0.0f }, intersectionPoint);
}

std::optional<ScatterRecord> Intersection::scatter(const Ray& ray) const {
    return m_material->scatter(ray, normal, intersectionPoint);
}

}  // namespace lm
