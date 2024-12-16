#pragma once

#include "math/Vec3.hpp"
#include <GLFW/glfw3.h>

namespace Engine {

class Camera {
public:
    Camera(const Math::Vec3& position = Math::Vec3(0.0f, 0.0f, 0.0f));

    void Update(float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    
    // Getters
    const Math::Vec3& GetPosition() const { return m_Position; }
    const Math::Vec3& GetFront() const { return m_Front; }
    const Math::Vec3& GetUp() const { return m_Up; }
    const Math::Vec3& GetRight() const { return m_Right; }
    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }

    // Movement
    void MoveForward(float deltaTime);
    void MoveBackward(float deltaTime);
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);

private:
    void UpdateCameraVectors();

    Math::Vec3 m_Position;
    Math::Vec3 m_Front;
    Math::Vec3 m_Up;
    Math::Vec3 m_Right;
    Math::Vec3 m_WorldUp;

    // Euler angles
    float m_Yaw;
    float m_Pitch;

    // Camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;

    static constexpr float DEFAULT_YAW = -90.0f;
    static constexpr float DEFAULT_PITCH = 0.0f;
    static constexpr float DEFAULT_SPEED = 5.0f;
    static constexpr float DEFAULT_SENSITIVITY = 0.1f;
};

} // namespace Engine
