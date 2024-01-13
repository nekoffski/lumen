#include <iostream>

#include "core/Core.h"
#include "core/Image.h"
#include "core/Camera.h"

#include "geometry/Sphere.h"
#include "geometry/IntersectableCollection.h"

#include "Scene.h"
#include "Renderer.h"

int main() {
    kc::core::initLogging("lumen");

    constexpr lm::u64 width  = 800;
    constexpr lm::u64 height = 600;

    lm::Camera::Properties cameraProps{
        .position      = lm::Vec3f{0.0f,  0.0f, -2.5f},
        .target        = lm::Vec3f{ 0.0f, 0.0f, 0.0f },
        .verticalFOV   = 40.0f,
        .aperture      = 1.0f,
        .focusDistance = 1.0f,
        .aspectRatio   = static_cast<lm::Float>(width) / height
    };
    lm::Camera camera{ cameraProps };

    lm::Sphere sphere{
        lm::Vec3f{-1.0f, 0.0f, 5.5f},
        1.0f, lm::Vec3f{ 0.0f, 1.0f, 0.0f}
    };
    lm::Sphere sphere2{
        lm::Vec3f{1.0f,  0.0f, 7.5f},
        1.0f, lm::Vec3f{ 1.0f, 0.0f, 0.0f}
    };
    lm::Scene scene;
    scene.world.add(&sphere).add(&sphere2);

    lm::Renderer::Properties props{
        .frameWidth      = width,
        .frameHeight     = height,
        .recursionDepth  = 16,
        .samplesPerPixel = 16
    };
    lm::Renderer renderer{ props, &camera };
    const auto image = renderer.render(scene);

    image.save("test.jpg");
    return 0;
}
