#pragma once

#include <kc/math/Format.h>
#include <kc/math/Utils.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace lm {

using namespace kc::math;
using namespace glm;

using Vec2f = vec2;
using Vec3f = vec3;
using Vec4f = vec4;

using Mat2f = mat2;
using Mat3f = mat3;
using Mat4f = mat4;

inline Vec3f operator*(const Mat4f& lhs, const Vec3f& rhs) {
    return Vec3f{
        lhs * Vec4f{rhs, 1.0f}
    };
}

const Mat4f identityMatrix = Mat4f{ 1.0f };

const Vec3f worldUp    = Vec3f{ 0.0f, 1.0f, 0.0f };
const Vec3f worldRight = Vec3f{ 1.0f, 0.0f, 0.0 };
const Vec3f worldFront = Vec3f{ 0.0f, 0.0f, 1.0f };

}  // namespace lm
