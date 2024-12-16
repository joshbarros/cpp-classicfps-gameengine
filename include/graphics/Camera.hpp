#pragma once

#include "math/Vec3.hpp"
#include "math/Mat4.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

class Camera {
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
    ~Camera() = default;

    void UpdatePosition(const glm::vec3& offset);
    void UpdateRotation(float xoffset, float yoffset);
    void SetPosition(const glm::vec3& position) { m_Position = position; }
    
    glm::mat4 GetViewMatrix() const;
    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetForward() const { return m_Front; }
    glm::vec3 GetRight() const { return m_Right; }
    glm::vec3 GetUp() const { return m_Up; }

private:
    void UpdateVectors();

    glm::vec3 m_Position;
    glm::vec3 m_Front{0.0f, 0.0f, -1.0f};
    glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_Right{1.0f, 0.0f, 0.0f};
    glm::vec3 m_WorldUp{0.0f, 1.0f, 0.0f};

    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;

    float m_MovementSpeed = 2.5f;
    float m_MouseSensitivity = 0.1f;
    float m_Zoom = 45.0f;
};

} // namespace Engine
