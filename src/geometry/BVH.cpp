#include "BVH.h"

namespace lm {

BVHNode::Wrapper::Wrapper(Intersectable* object) : m_object(object) {}

std::optional<Intersection> BVHNode::Wrapper::intersect(
  const Ray& ray, const Interval& interval
) const {
    return m_object->intersect(ray, interval);
}

const BoundingVolume* BVHNode::Wrapper::getBoundingVolume() const {
    return m_object->getBoundingVolume();
}

BVHNode::BVHNode(const std::vector<Intersectable*>& objects) :
    BVHNode(objects, 0, objects.size()) {}

BVHNode::BVHNode(const std::vector<Intersectable*>& objects, u64 start, u64 end) {
    auto localObjects = objects;
    auto axis         = random<u16>(0, 2);
    auto comparator =
      (axis == 0) ? xBoxCompare
      : (axis == 1)
        ? yBoxCompare
        : zBoxCompare;

    const u64 objectCount = end - start;
    LOG_TRACE(
      "Creating BVH Node, object count={}, intersecting withing axis={}",
      objectCount, axis
    );

    if (objectCount == 1) {
        m_left = m_right = std::make_shared<Wrapper>(localObjects[start]);
    } else if (objectCount == 2) {
        if (comparator(localObjects[start], localObjects[start + 1])) {
            m_left  = std::make_shared<Wrapper>(localObjects[start]);
            m_right = std::make_shared<Wrapper>(localObjects[start + 1]);
        } else {
            m_left  = std::make_shared<Wrapper>(localObjects[start + 1]);
            m_right = std::make_shared<Wrapper>(localObjects[start]);
        }
    } else {
        std::sort(
          localObjects.begin() + start, localObjects.begin() + end, comparator
        );

        const auto mid = start + objectCount / 2;

        m_left  = std::make_shared<BVHNode>(localObjects, start, mid);
        m_right = std::make_shared<BVHNode>(localObjects, mid, end);
    }

    m_boundingVolume.mergeWith(*static_cast<const AABB*>(m_left->getBoundingVolume())
    );
    m_boundingVolume.mergeWith(*static_cast<const AABB*>(m_right->getBoundingVolume()
    ));
}

bool BVHNode::boxCompare(Intersectable* a, Intersectable* b, u16 axis) {
    auto l = static_cast<const AABB*>(a->getBoundingVolume());
    auto r = static_cast<const AABB*>(b->getBoundingVolume());
    return l->getMin()[axis] < r->getMin()[axis];
}

bool BVHNode::xBoxCompare(Intersectable* a, Intersectable* b) {
    return boxCompare(a, b, 0);
}

bool BVHNode::yBoxCompare(Intersectable* a, Intersectable* b) {
    return boxCompare(a, b, 1);
}

bool BVHNode::zBoxCompare(Intersectable* a, Intersectable* b) {
    return boxCompare(a, b, 2);
}

std::optional<Intersection> BVHNode::intersect(
  const Ray& ray, const Interval& interval
) const {
    if (not m_boundingVolume.intersects(ray, interval)) return {};

    if (auto leftHit = m_left->intersect(ray, interval); leftHit) {
        auto rightHit = m_right->intersect(
          ray,
          Interval(
            std::max(interval.min, leftHit->t), std::min(interval.max, leftHit->t)
          )
        );
        if (rightHit) return leftHit->t < rightHit->t ? leftHit : rightHit;
        return leftHit;
    }
    return m_right->intersect(ray, interval);
}

const BoundingVolume* BVHNode::getBoundingVolume() const {
    return &m_boundingVolume;
}

}  // namespace lm
