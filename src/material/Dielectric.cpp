#include "Dielectric.h"

#include "core/Math.h"

namespace lm {

Dielectric::Dielectric(Float indexOfRefraction) :
    m_indexOfRefraction(indexOfRefraction), m_attenuation(1.0f) {}

const Texture* Dielectric::getTexture() const { return &m_attenuation; }

static Float getReflectance(Float cosine, Float ior) {
    auto r0 = (1.0 - ior) / (1.0 + ior);
    r0 *= r0;
    return r0 + (1.0f - r0) * std::pow(1 - cosine, 5);
}

std::optional<ScatterRecord> Dielectric::scatter(
  const Ray& ray, const Vec3f& normal, const Vec3f& intersectionPoint
) const {
    auto direction = normalize(ray.direction);

    const auto cosTheta = std::min(1.0f, dot(-direction, normal));
    const auto sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    const auto ior = 1.0f / m_indexOfRefraction;

    const auto refracts =
      (ior * sinTheta <= 1.0f) || (getReflectance(cosTheta, ior) > random<Float>());

    return refracts ? ScatterRecord{ refract(direction, normal, ior) }
                    : ScatterRecord{ reflect(direction, normal) };
}

}  // namespace lm
