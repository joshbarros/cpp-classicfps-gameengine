#pragma once

#include "graphics/Camera.hpp"
#include "player/PlayerController.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Mesh.hpp"
#include "debug/Debug.hpp"
#include <memory>
#include <GLFW/glfw3.h>

namespace Engine {

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize();
    void Run();

private:
    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
    void HandleMouseMovement();

    GLFWwindow* m_Window;
    bool m_Running;
    float m_LastFrameTime;
    bool m_FirstMouse;
    float m_LastX, m_LastY;
    
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<PlayerController> m_Player;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh> m_FloorMesh;
};

} // namespace Engine
