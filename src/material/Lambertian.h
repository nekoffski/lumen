#pragma once

#include "Material.h"
#include "texture/Texture.h"

namespace lm {

class Lambertian : public Material {
public:
    explicit Lambertian(Texture* texture);

    Texture* getTexture() const override;

private:
    Texture* m_texture;
};

}  // namespace lm
