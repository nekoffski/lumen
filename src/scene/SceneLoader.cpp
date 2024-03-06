#include "Scene.h"
#include "SceneLoader.h"

#include "core/Core.h"

#include <kc/core/FileSystem.h>
#include <kc/json/Utils.hpp>

#include "texture/SolidColor.h"

#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "material/DiffuseLight.h"

#include "geometry/Sphere.h"
#include "geometry/Quad.h"
#include "geometry/Box.h"
#include "geometry/Instance.h"

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
        } else if (r.type == "dielectric") {
            const auto ior = getField<Float>(r.object, "index-of-refraction");
            m_scene->addMaterial<Dielectric>(r.name, ior);
        } else if (r.type == "diffuse-light") {
            const auto textureName = getField<std::string>(r.object, "texture");
            const auto texture     = m_scene->getTexture(textureName);
            m_scene->addMaterial<DiffuseLight>(r.name, texture);
        }
    });
}

void SceneLoader::processObjects(const kc::json::Node& root) {
    LOG_INFO("Processing objects");
    processFields(root, [&](const Record& r) {
        LOG_TRACE("\tProcessing object: {}", r.type);

        auto createObject = [&]() -> Intersectable* {
            if (r.type == "sphere") {
                const auto position = getField<Vec3f>(r.object, "position");
                const auto radius   = getField<Float>(r.object, "radius");
                const auto materialName =
                  getField<std::string>(r.object, "material");
                const auto material = m_scene->getMaterial(materialName);
                return m_scene->createObject<Sphere>(
                  r.name, position, radius, material
                );
            } else if (r.type == "quad") {
                const auto origin = getField<Vec3f>(r.object, "origin");
                const auto u      = getField<Vec3f>(r.object, "u");
                const auto v      = getField<Vec3f>(r.object, "v");
                const auto materialName =
                  getField<std::string>(r.object, "material");
                const auto material = m_scene->getMaterial(materialName);
                return m_scene->createObject<Quad>(r.name, origin, u, v, material);
            } else if (r.type == "box") {
                const auto min = getField<Vec3f>(r.object, "min");
                const auto max = getField<Vec3f>(r.object, "max");
                const auto materialName =
                  getField<std::string>(r.object, "material");
                const auto material = m_scene->getMaterial(materialName);
                return m_scene->createObject<Box>(r.name, min, max, material);
            }
            return nullptr;
        };
        const auto name = fmt::format("Instance_{}", r.name);
        auto object     = createObject();
        ASSERT(object, "Could not process object");
        auto instance = m_scene->addObject<Instance>(name, object);

        for (auto transform : r.object["transforms"]) {
            const auto type  = transform.getMemberNames()[0];
            const auto value = getField<Vec3f>(transform, type);
            LOG_TRACE("\tTransform: {} - {}", type, value);

            if (type == "translate")
                instance->addTransform<Translate>(value);
            else if (type == "rotation")
                instance->addTransform<Rotation>(value);
        }
    });
}

}  // namespace lm
