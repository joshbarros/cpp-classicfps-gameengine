#pragma once

#include "Vec3.hpp"
#include <cmath>
#include <array>

namespace Engine {
namespace Math {

class Mat4 {
public:
    std::array<float, 16> elements;

    Mat4() {
        for (int i = 0; i < 16; i++) {
            elements[i] = 0.0f;
        }
        elements[0] = elements[5] = elements[10] = elements[15] = 1.0f;
    }

    static Mat4 Perspective(float fov, float aspect, float near, float far) {
        Mat4 result;
        float tanHalfFov = std::tan(fov / 2.0f);
        
        result.elements[0] = 1.0f / (aspect * tanHalfFov);
        result.elements[5] = 1.0f / tanHalfFov;
        result.elements[10] = -(far + near) / (far - near);
        result.elements[11] = -1.0f;
        result.elements[14] = -(2.0f * far * near) / (far - near);
        result.elements[15] = 0.0f;
        
        return result;
    }

    static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        Mat4 result;
        
        Vec3 f = (center - eye).Normalized();
        Vec3 s = f.Cross(up).Normalized();
        Vec3 u = s.Cross(f);
        
        result.elements[0] = s.x;
        result.elements[1] = u.x;
        result.elements[2] = -f.x;
        result.elements[3] = 0.0f;
        
        result.elements[4] = s.y;
        result.elements[5] = u.y;
        result.elements[6] = -f.y;
        result.elements[7] = 0.0f;
        
        result.elements[8] = s.z;
        result.elements[9] = u.z;
        result.elements[10] = -f.z;
        result.elements[11] = 0.0f;
        
        result.elements[12] = -s.Dot(eye);
        result.elements[13] = -u.Dot(eye);
        result.elements[14] = f.Dot(eye);
        result.elements[15] = 1.0f;
        
        return result;
    }

    static Mat4 Translate(const Vec3& translation) {
        Mat4 result;
        
        result.elements[12] = translation.x;
        result.elements[13] = translation.y;
        result.elements[14] = translation.z;
        
        return result;
    }

    const float* Data() const { return elements.data(); }
};

} // namespace Math
} // namespace Engine
