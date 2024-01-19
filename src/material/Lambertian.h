#pragma once

#include "Material.h"
#include "texture/Texture.h"

namespace lm {

class Lambertian : public Material {
public:
    explicit Lambertian(Texture* texture);

    Texture* getTexture() const override;

    std::optional<ScatterRecord> scatter(
      const Vec3f& normal, const Vec3f& intersectionPoint
    ) const override;

private:
    Texture* m_texture;
};

}  // namespace lm
