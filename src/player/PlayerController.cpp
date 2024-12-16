#include "player/PlayerController.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include "core/Input.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace Engine {

PlayerController::PlayerController(std::shared_ptr<Camera> camera)
    : m_Camera(camera)
    , m_Position(0.0f, 2.0f, 0.0f)
    , m_Velocity(0.0f)
    , m_IsGrounded(true)
    , m_IsCrouching(false)
    , m_StandingHeight(2.0f)
    , m_CrouchHeight(1.0f)
    , m_CurrentHeight(2.0f) {
    m_Camera->SetPosition(m_Position);
}

void PlayerController::ProcessKeyboard(float deltaTime) {
    const float speed = m_IsGrounded ? 320.0f : 96.0f; // 30% speed in air
    glm::vec3 movement(0.0f);

    GLFWwindow* window = glfwGetCurrentContext();

    // Forward/Backward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement += m_Camera->GetForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement -= m_Camera->GetForward();

    // Left/Right
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement -= m_Camera->GetRight();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement += m_Camera->GetRight();

    // Make movement planar (no vertical component from camera angle)
    movement.y = 0;
    if (glm::length(movement) > 0)
        movement = glm::normalize(movement);

    // Apply speed
    movement *= speed * deltaTime;

    // Jump
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && m_IsGrounded) {
        m_Velocity.y = 350.0f; // Jump velocity
        m_IsGrounded = false;
    }

    // Crouch
    bool shouldCrouch = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
    if (shouldCrouch != m_IsCrouching) {
        m_IsCrouching = shouldCrouch;
        m_CurrentHeight = m_IsCrouching ? m_CrouchHeight : m_StandingHeight;
        // Adjust camera height
        m_Position.y = m_CurrentHeight;
        m_Camera->SetPosition(m_Position);
    }

    // Apply gravity
    if (!m_IsGrounded) {
        m_Velocity.y += -800.0f * deltaTime; // Gravity
    }

    // Update position
    m_Position += movement;
    m_Position.y += m_Velocity.y * deltaTime;

    // Ground check
    if (m_Position.y <= m_CurrentHeight) {
        m_Position.y = m_CurrentHeight;
        m_Velocity.y = 0.0f;
        m_IsGrounded = true;
    }

    // Update camera position
    m_Camera->SetPosition(m_Position);
}

void PlayerController::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    m_Camera->UpdateRotation(xoffset, yoffset);
}

glm::vec3 PlayerController::GetPosition() const {
    return m_Position;
}

glm::vec3 PlayerController::GetVelocity() const {
    return m_Velocity;
}

bool PlayerController::IsGrounded() const {
    return m_IsGrounded;
}

} // namespace Engine
