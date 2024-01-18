#pragma once

#include <optional>
#include <string>

#include <kc/mem/LocalPtr.hpp>
#include <kc/json/Json.h>

#include "core/Core.h"

#include "Scene.h"

namespace lm {

class SceneLoader {
public:
    struct Config {
        std::string filePath;
        Float fov;
    };

    explicit SceneLoader(const Config& config);

    std::optional<Scene> load() &&;

private:
    void processCamera(const kc::json::Node& root);
    void processTextures(const kc::json::Node& root);
    void processMaterials(const kc::json::Node& root);
    void processObjects(const kc::json::Node& root);

    std::optional<Scene> m_scene;
    Config m_config;
};

}  // namespace lm