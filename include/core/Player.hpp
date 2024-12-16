#pragma once

#include "physics/Physics.hpp"
#include <memory>

namespace Engine {

class Player {
public:
    Player();
    ~Player() = default;

    void Update(float deltaTime);
    void Move(const glm::vec3& direction, float deltaTime);
    void Jump();
    void Crouch(bool crouching);

    const glm::vec3& GetPosition() const { return m_Physics->GetPosition(); }
    const glm::vec3& GetVelocity() const { return m_Physics->GetVelocity(); }
    bool IsGrounded() const { return m_Physics->IsGrounded(); }
    float GetHeight() const { return m_Height; }

private:
    std::unique_ptr<Physics> m_Physics;
    float m_Height = 1.8f;  // Default player height in meters
    float m_CrouchHeight = 0.9f;
    float m_MoveSpeed = 5.0f;
    float m_JumpForce = 5.0f;
    bool m_IsCrouching = false;
};

} // namespace Engine
