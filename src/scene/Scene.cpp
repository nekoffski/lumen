#include "Scene.h"

namespace lm {

Scene::Scene(const Camera::Properties& cameraProperties) :
    m_camera(cameraProperties), m_useBVH(true), m_bvh(nullptr) {}

Camera* Scene::getCamera() { return &m_camera; }

Intersectable* Scene::getWorld() {
    if (m_useBVH) {
        if (not m_bvh) m_bvh = std::make_shared<BVHNode>(m_world.getObjects());
        return m_bvh.get();
    }
    m_world.buildBoundingVolume();
    return &m_world;
}

}  // namespace lm
