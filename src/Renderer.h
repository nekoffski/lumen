#pragma once

#include "core/Core.h"
#include "core/Camera.h"
#include "core/Image.h"
#include "Scene.h"

namespace lm {

class Renderer {
public:
    struct Properties {
        u64 frameWidth;
        u64 frameHeight;
        u64 recursionDepth;
        u64 samplesPerPixel;
    };

    explicit Renderer(const Properties& properties, Camera* camera);

    Image render(const Scene& scene);

private:
    Coordinates<Float> toNDC(const Coordinates<i64>& coordinates);

    Vec3f traceRay(const Ray& ray, const Intersectable& world, u64 recursionDepth);

    Properties m_props;
    Camera* m_camera;

    Float m_frameWidthNumeric;
    Float m_frameHeightNumeric;
    Float m_halfFrameWidth;
    Float m_halfFrameHeight;
};

}  // namespace lm
