#pragma once

#include "graphics/Camera.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace Engine {

class PlayerController {
public:
    explicit PlayerController(std::shared_ptr<Camera> camera);

    void ProcessKeyboard(float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    glm::vec3 GetPosition() const;
    glm::vec3 GetVelocity() const;
    bool IsGrounded() const;

private:
    std::shared_ptr<Camera> m_Camera;
    glm::vec3 m_Position;
    glm::vec3 m_Velocity;
    bool m_IsGrounded;
    bool m_IsCrouching;
    float m_StandingHeight;
    float m_CrouchHeight;
    float m_CurrentHeight;
};

} // namespace Engine
