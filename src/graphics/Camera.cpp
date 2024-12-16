#include "graphics/Camera.hpp"
#include <cmath>

namespace Engine {

Camera::Camera(const glm::vec3& position)
    : m_Position(position)
    , m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f))
    , m_Yaw(-90.0f)
    , m_Pitch(0.0f)
{
    UpdateVectors();
}

void Camera::UpdateRotation(float xOffset, float yOffset) {
    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    // Constrain pitch
    if (m_Pitch > 89.0f) {
        m_Pitch = 89.0f;
    }
    if (m_Pitch < -89.0f) {
        m_Pitch = -89.0f;
    }

    UpdateVectors();
}

void Camera::UpdatePosition(const glm::vec3& offset) {
    m_Position += offset;
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::UpdateVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);

    // Re-calculate the Right and Up vector
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

} // namespace Engine
