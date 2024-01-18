#include <iostream>

#include "core/Core.h"
#include "core/Image.h"
#include "core/Camera.h"

#include "geometry/Sphere.h"
#include "geometry/IntersectableCollection.h"

#include "scene/SceneLoader.h"
#include "scene/Scene.h"

#include "Renderer.h"

#include "material/Lambertian.h"
#include "texture/SolidColor.h"

int main(int argc, char** argv) {
    kc::core::initLogging("lumen");

    constexpr lm::u64 width  = 800;
    constexpr lm::u64 height = 600;
    constexpr lm::Float fov  = static_cast<lm::Float>(width) / height;

    lm::SceneLoader::Config sceneLoaderConfig{
        .filePath = "../scenes/test.json", .fov = fov
    };
    auto scene = lm::SceneLoader{ sceneLoaderConfig }.load();

    lm::Renderer::Properties props{
        .frameWidth      = width,
        .frameHeight     = height,
        .recursionDepth  = 16,
        .samplesPerPixel = 16
    };
    lm::Renderer renderer{ props, scene->getCamera() };
    lm::RenderPacket renderPacket{ scene->getWorld() };
    const auto image = renderer.render(renderPacket);

    image.save("test.jpg");
    return 0;
}
