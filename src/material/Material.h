#pragma once

#include "texture/Texture.h"

namespace lm {

struct Material {
    virtual Texture* getTexture() const = 0;
};

}  // namespace lm
