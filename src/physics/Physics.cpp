#include "physics/Physics.hpp"
#include <algorithm>

namespace Engine {

void Physics::Update(float deltaTime) {
    // Apply gravity if not grounded
    if (!m_IsGrounded) {
        m_Acceleration.y = GRAVITY;
    } else {
        m_Acceleration.y = 0.0f;
        if (m_Velocity.y < 0) {
            m_Velocity.y = 0.0f;
        }
    }

    // Update velocity
    m_Velocity += m_Acceleration * deltaTime;

    // Clamp vertical velocity to terminal velocity
    m_Velocity.y = std::max(m_Velocity.y, TERMINAL_VELOCITY);

    // Update position
    m_Position += m_Velocity * deltaTime;

    // Reset acceleration
    m_Acceleration = glm::vec3(0.0f);

    // Ground check (simple for now)
    if (m_Position.y < 0.0f) {
        m_Position.y = 0.0f;
        m_IsGrounded = true;
    }
}

void Physics::ApplyForce(const glm::vec3& force) {
    m_Acceleration += force;
}

} // namespace Engine
