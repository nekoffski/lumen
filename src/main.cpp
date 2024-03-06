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

#include "Input.h"

lm::Scene getScene(const lm::Config& cfg) {
    if (cfg.random) {
        // TODO:
    } else {
        lm::SceneLoader::Config sceneLoaderConfig{
            .filePath = *cfg.inputPath, .fov = cfg.fov
        };
        auto scene = lm::SceneLoader{ sceneLoaderConfig }.load();
        ASSERT(scene, "Could not load scene");
        return *scene;
    }
}

int main(int argc, char** argv) {
    kc::core::initLogging("lumen");

    auto config = lm::Input{ argc, argv }.getConfig();
    if (not config) return 0;

    auto scene = getScene(*config);

    lm::Renderer::Properties props{
        .frameWidth      = config->width,
        .frameHeight     = config->height,
        .recursionDepth  = config->recursionDepth,
        .samplesPerPixel = config->samplesPerPixel,
        .parallel        = config->parallel
    };
    lm::Renderer renderer{ props, scene.getCamera() };
    lm::RenderPacket renderPacket{ scene.getWorld() };
    const auto image = renderer.render(renderPacket);

    image.save(config->output);
    return 0;
}
