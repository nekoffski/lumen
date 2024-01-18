#pragma once

#include <memory>
#include <unordered_map>

#include "geometry/IntersectableCollection.h"
#include "geometry/Intersectable.h"
#include "material/Material.h"
#include "texture/Texture.h"
#include "core/Camera.h"

namespace lm {

class Scene {
    template <typename K, typename V>
    using PtrMap = std::unordered_map<K, std::shared_ptr<V>>;

public:
    explicit Scene(const Camera::Properties& cameraProperties);

    Intersectable* getWorld();
    Camera* getCamera();

    template <typename T, typename... Args>
    void addMaterial(const std::string& name, Args&&... args) {
        m_materials.emplace(name, std::make_shared<T>(std::forward<Args>(args)...));
    }

    template <typename T, typename... Args>
    void addTexture(const std::string& name, Args&&... args) {
        m_textures.emplace(name, std::make_shared<T>(std::forward<Args>(args)...));
    }

    template <typename T, typename... Args>
    void addObject(const std::string& name, Args&&... args) {
        m_objects.emplace(name, std::make_shared<T>(std::forward<Args>(args)...));
        m_world.add(m_objects[name].get());
    }

    Texture* getTexture(const std::string& name) { return m_textures[name].get(); }
    Material* getMaterial(const std::string& name) {
        return m_materials[name].get();
    }

private:
    PtrMap<std::string, Material> m_materials;
    PtrMap<std::string, Intersectable> m_objects;
    PtrMap<std::string, Texture> m_textures;

    IntersectableCollection m_world;
    Camera m_camera;
};

}  // namespace lm
