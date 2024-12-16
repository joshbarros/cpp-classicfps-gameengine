#include "core/Player.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

Player::Player() {
    m_Physics = std::make_unique<Physics>();
    m_Physics->SetPosition(glm::vec3(0.0f, m_Height, 0.0f));
}

void Player::Update(float deltaTime) {
    m_Physics->Update(deltaTime);
}

void Player::Move(const glm::vec3& direction, float deltaTime) {
    float speed = m_IsCrouching ? m_MoveSpeed * 0.5f : m_MoveSpeed;
    glm::vec3 velocity = direction * speed;
    
    // Only update horizontal velocity (x and z)
    m_Physics->SetVelocity(glm::vec3(
        velocity.x,
        m_Physics->GetVelocity().y,
        velocity.z
    ));
}

void Player::Jump() {
    if (m_Physics->IsGrounded()) {
        glm::vec3 velocity = m_Physics->GetVelocity();
        velocity.y = m_JumpForce;
        m_Physics->SetVelocity(velocity);
        m_Physics->SetGrounded(false);
    }
}

void Player::Crouch(bool crouching) {
    if (m_IsCrouching != crouching) {
        m_IsCrouching = crouching;
        float newHeight = crouching ? m_CrouchHeight : m_Height;
        
        // Adjust position to account for height change
        glm::vec3 pos = m_Physics->GetPosition();
        pos.y = newHeight;
        m_Physics->SetPosition(pos);
    }
}

} // namespace Engine
