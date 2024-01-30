#pragma once

#include "core/Core.h"
#include "core/Camera.h"
#include "core/Image.h"
#include "geometry/Intersectable.h"

namespace lm {

struct RenderPacket {
    Intersectable* world;
};

class Renderer {
public:
    struct Properties {
        u64 frameWidth;
        u64 frameHeight;
        u64 recursionDepth;
        u64 samplesPerPixel;
        bool parallel;
    };

    explicit Renderer(const Properties& properties, Camera* camera);

    Image render(const RenderPacket& renderPacket);

private:
    Float getRandomThrottle() const;

    Coordinates<Float> toNDC(const Coordinates<i64>& coordinates);

    Vec3f traceRay(const Ray& ray, Intersectable* world, u64 recursionDepth);

    Properties m_props;
    Camera* m_camera;

    Float m_frameWidthNumeric;
    Float m_frameHeightNumeric;
    Float m_halfFrameWidth;
    Float m_halfFrameHeight;
};

}  // namespace lm
