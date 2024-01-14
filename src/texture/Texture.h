#pragma once

#include "core/Core.h"
#include "core/Math.h"

namespace lm {

struct Texture {
    virtual Vec3f getColor(const Coordinates<Float>& uv) const = 0;
};

}  // namespace lm
