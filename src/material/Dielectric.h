#pragma once

#include "Material.h"

#include "texture/Texture.h"
#include "texture/SolidColor.h"

namespace lm {

class Dielectric : public Material {
public:
    explicit Dielectric(Float indexOfRefraction);

    const Texture* getTexture() const override;

    std::optional<ScatterRecord> scatter(
      const Ray& ray, const Vec3f& normal, const Vec3f& intersectionPoint
    ) const override;

private:
    Float m_indexOfRefraction;
    SolidColor m_attenuation;
};

}  // namespace lm
