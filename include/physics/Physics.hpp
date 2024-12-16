#pragma once

#include <glm/glm.hpp>

namespace Engine {

class Physics {
public:
    static constexpr float GRAVITY = -9.81f;
    static constexpr float TERMINAL_VELOCITY = -50.0f;

    Physics() = default;
    ~Physics() = default;

    void Update(float deltaTime);
    void ApplyForce(const glm::vec3& force);
    void SetPosition(const glm::vec3& position) { m_Position = position; }
    void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
    void SetGrounded(bool grounded) { m_IsGrounded = grounded; }

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetVelocity() const { return m_Velocity; }
    bool IsGrounded() const { return m_IsGrounded; }

private:
    glm::vec3 m_Position{0.0f};
    glm::vec3 m_Velocity{0.0f};
    glm::vec3 m_Acceleration{0.0f};
    bool m_IsGrounded = false;
};

} // namespace Engine
