#pragma once

#include "Core.h"
#include "Ray.h"

namespace lm {

class Camera {
public:
    struct Properties {
        Vec3f position;
        Vec3f target;
        Float verticalFOV;
        Float aperture;
        Float focusDistance;
        Float aspectRatio;
    };

    explicit Camera(const Properties& props);

    Ray getRay(const Coordinates<Float>& coords);

private:
    Properties m_props;

    Vec3f m_center;
    Vec3f m_horizontal;
    Vec3f m_vertical;
    Vec3f m_u;
    Vec3f m_v;
    Vec3f m_w;

    Float m_lensRadius;
};

}  // namespace lm