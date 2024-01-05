#pragma once

#include "Core.h"
#include "Ray.h"

namespace lm {

class Camera {
public:
    struct Properties {
        u64 viewportWidth;
        u64 viewportHeight;

        Vec3f position;
    };

    explicit Camera(const Properties& props);

    Ray getRay(const Coordinates& coords);

private:
    Properties m_props;

    const Float m_halfWidth;
    const Float m_halfHeight;
};

}  // namespace lm