#include "Scene.h"

namespace lm {

Scene::Scene(const Camera::Properties& cameraProperties) :
    m_camera(cameraProperties) {}

Camera* Scene::getCamera() { return &m_camera; }

Intersectable* Scene::getWorld() { return &m_world; }

}  // namespace lm
