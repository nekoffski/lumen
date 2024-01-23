#include "Scene.h"
#include "SceneLoader.h"

#include "core/Core.h"

#include <kc/core/FileSystem.h>
#include <kc/json/Utils.hpp>

#include "texture/SolidColor.h"
#include "material/Lambertian.h"
#include "material/Metal.h"

#include "geometry/Sphere.h"

namespace lm {

auto fieldFrom(auto& root) { return kc::json::fieldFrom<kc::json::JsonError>(root); }

template <typename T> T getField(auto& root, const std::string& name) {
    return fieldFrom(root).withName(name).template ofType<T>().get();
}

auto getArray(auto& root, const std::string& name) {
    return fieldFrom(root).withName(name).asArray().get();
}

SceneLoader::SceneLoader(const Config& config) : m_config(config) {}

std::optional<Scene> SceneLoader::load() && try {
    kc::core::FileSystem fs;

    LOG_INFO("Processing scene: {}", m_config.filePath);

    if (not fs.isFile(m_config.filePath)) {
        LOG_ERROR("Could not open scene file: {}", m_config.filePath);
        return {};
    }

    const auto root = kc::json::loadJson(fs.readFile(m_config.filePath));
    LOG_INFO("Scene file found and parsed to JSON");

    processCamera(root["camera"]);
    processTextures(root["textures"]);
    processMaterials(root["materials"]);
    processObjects(root["objects"]);

    return m_scene;

} catch (const kc::json::JsonError& err) {
    LOG_ERROR("Could not process scene file: {}", err.asString());
    return {};
}

void SceneLoader::processCamera(const kc::json::Node& root) {
    LOG_INFO("Processing camera");
    Camera::Properties cameraProps{
        .position      = getField<Vec3f>(root, "position"),
        .target        = getField<Vec3f>(root, "target"),
        .verticalFOV   = getField<Float>(root, "vertical-fov"),
        .aperture      = getField<Float>(root, "aperture"),
        .focusDistance = getField<Float>(root, "focus-distance"),
        .aspectRatio   = m_config.fov
    };

    m_scene.emplace(cameraProps);
}

struct Record {
    kc::json::Node object;
    std::string name;
    std::string type;
};

static void processFields(
  const kc::json::Node& root, std::function<void(const Record& record)>&& callback
) {
    for (const auto& name : root.getMemberNames()) {
        const auto& object = root[name];
        callback(Record{
          .object = object,
          .name   = name,
          .type   = getField<std::string>(object, "type"),
        });
    }
}

void SceneLoader::processTextures(const kc::json::Node& root) {
    LOG_INFO("Processing textures");
    processFields(root, [&](const Record& r) {
        if (r.type == "solid") {
            const auto color = getField<Vec3f>(r.object, "color");
            m_scene->addTexture<SolidColor>(r.name, color);
        }
    });
}

void SceneLoader::processMaterials(const kc::json::Node& root) {
    LOG_INFO("Processing materials");
    processFields(root, [&](const Record& r) {
        if (r.type == "lambertian") {
            const auto textureName = getField<std::string>(r.object, "texture");
            const auto texture     = m_scene->getTexture(textureName);
            m_scene->addMaterial<Lambertian>(r.name, texture);
        } else if (r.type == "metal") {
            const auto textureName = getField<std::string>(r.object, "texture");
            const auto fuzziness   = getField<Float>(r.object, "fuzziness");
            const auto texture     = m_scene->getTexture(textureName);
            m_scene->addMaterial<Metal>(r.name, texture, fuzziness);
        }
    });
}

void SceneLoader::processObjects(const kc::json::Node& root) {
    LOG_INFO("Processing objects");
    processFields(root, [&](const Record& r) {
        if (r.type == "sphere") {
            const auto position     = getField<Vec3f>(r.object, "position");
            const auto radius       = getField<Float>(r.object, "radius");
            const auto materialName = getField<std::string>(r.object, "material");
            const auto material     = m_scene->getMaterial(materialName);
            m_scene->addObject<Sphere>(r.name, position, radius, material);
        }
    });
}

}  // namespace lm
