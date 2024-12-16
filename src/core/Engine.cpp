#include "core/Engine.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>
#include <thread>

namespace Engine {

Engine::Engine()
    : m_Window(nullptr)
    , m_Running(false)
    , m_LastFrameTime(0.0f)
    , m_FirstMouse(true)
    , m_LastX(400.0f)
    , m_LastY(300.0f) {
}

Engine::~Engine() {
    Debug::Shutdown();
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

bool Engine::Initialize() {
    try {
        std::cout << "Initializing GLFW..." << std::endl;
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        // Set OpenGL version and profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        std::cout << "Creating window..." << std::endl;
        m_Window = glfwCreateWindow(800, 600, "Classic FPS Engine", nullptr, nullptr);
        if (!m_Window) {
            const char* description;
            int code = glfwGetError(&description);
            std::cerr << "Failed to create GLFW window. Error " << code << ": " << description << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        
        std::cout << "Initializing GLEW..." << std::endl;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
            return false;
        }

        // Print OpenGL version
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);

        // Initialize components
        std::cout << "Initializing components..." << std::endl;

        try {
            m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 2.0f, 5.0f));
            m_Player = std::make_shared<PlayerController>(m_Camera);
            m_Shader = std::make_shared<Shader>();
        } catch (const std::exception& e) {
            std::cerr << "Failed to initialize components: " << e.what() << std::endl;
            return false;
        }

        // Load shader
        std::cout << "Loading shaders..." << std::endl;
        try {
            if (!m_Shader->LoadFromFile("shaders/basic.vert", "shaders/basic.frag")) {
                std::cerr << "Failed to load shaders" << std::endl;
                return false;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception while loading shaders: " << e.what() << std::endl;
            return false;
        }

        // Create floor mesh (72x72 grid)
        std::cout << "Creating floor mesh..." << std::endl;
        try {
            std::vector<Vertex> vertices = {
                {{-36.0f, 0.0f, -36.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{ 36.0f, 0.0f, -36.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                {{ 36.0f, 0.0f,  36.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
                {{-36.0f, 0.0f,  36.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
            };

            std::vector<unsigned int> indices = {
                0, 1, 2,
                2, 3, 0
            };

            m_FloorMesh = std::make_shared<Mesh>(vertices, indices);
        } catch (const std::exception& e) {
            std::cerr << "Failed to create floor mesh: " << e.what() << std::endl;
            return false;
        }

        // Initialize debug UI
        std::cout << "Initializing Debug UI..." << std::endl;
        try {
            Debug::Initialize(m_Window);
        } catch (const std::exception& e) {
            std::cerr << "Failed to initialize Debug UI: " << e.what() << std::endl;
            return false;
        }

        // Set input mode after all initialization is done
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        m_Running = true;
        std::cout << "Initialization complete!" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error during initialization: " << e.what() << std::endl;
        return false;
    }
}

void Engine::Run() {
    if (!m_Running) {
        std::cerr << "Cannot run engine - not properly initialized" << std::endl;
        return;
    }

    float lastFrame = 0.0f;
    const float targetFrameTime = 1.0f / 60.0f; // 60 FPS

    std::cout << "Starting game loop..." << std::endl;

    while (m_Running && !glfwWindowShouldClose(m_Window)) {
        try {
            float currentFrame = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrame - lastFrame;

            // Cap framerate at 60 FPS
            if (deltaTime < targetFrameTime) {
                float sleepTime = (targetFrameTime - deltaTime) * 1000.0f;
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime)));
                currentFrame = static_cast<float>(glfwGetTime());
                deltaTime = currentFrame - lastFrame;
            }

            lastFrame = currentFrame;

            ProcessInput(deltaTime);
            HandleMouseMovement();
            Update(deltaTime);
            Render();

            // Update debug info
            Debug::SetFPS(1.0f / deltaTime);
            Debug::SetPlayerPosition(m_Player->GetPosition());
            Debug::SetPlayerVelocity(m_Player->GetVelocity());
            Debug::SetPlayerGrounded(m_Player->IsGrounded());

            Debug::NewFrame();
            Debug::Render();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();

        } catch (const std::exception& e) {
            std::cerr << "Error in game loop: " << e.what() << std::endl;
            m_Running = false;
        }
    }
}

void Engine::ProcessInput(float deltaTime) {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        m_Running = false;
    }

    // Toggle fullscreen with F11
    static bool wasF11Pressed = false;
    if (glfwGetKey(m_Window, GLFW_KEY_F11) == GLFW_PRESS) {
        if (!wasF11Pressed) {
            static int windowed_x = 0, windowed_y = 0;
            static int windowed_width = 800, windowed_height = 600;
            
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            if (glfwGetWindowMonitor(m_Window) == nullptr) {
                // Save windowed mode position and size
                glfwGetWindowPos(m_Window, &windowed_x, &windowed_y);
                glfwGetWindowSize(m_Window, &windowed_width, &windowed_height);
                
                // Switch to fullscreen
                glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            } else {
                // Switch back to windowed mode
                glfwSetWindowMonitor(m_Window, nullptr, windowed_x, windowed_y, windowed_width, windowed_height, 0);
            }
            wasF11Pressed = true;
        }
    } else {
        wasF11Pressed = false;
    }

    m_Player->ProcessKeyboard(deltaTime);
}

void Engine::Update(float deltaTime) {
    // Currently handled in ProcessInput
}

void Engine::HandleMouseMovement() {
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);

    if (m_FirstMouse) {
        m_LastX = static_cast<float>(xpos);
        m_LastY = static_cast<float>(ypos);
        m_FirstMouse = false;
        return;
    }

    float xoffset = static_cast<float>(xpos) - m_LastX;
    float yoffset = m_LastY - static_cast<float>(ypos);

    m_LastX = static_cast<float>(xpos);
    m_LastY = static_cast<float>(ypos);

    m_Player->ProcessMouseMovement(xoffset, yoffset);
}

void Engine::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
    glm::mat4 view = m_Camera->GetViewMatrix();

    m_Shader->SetMat4("projection", projection);
    m_Shader->SetMat4("view", view);

    // Render floor
    glm::mat4 model = glm::mat4(1.0f);
    m_Shader->SetMat4("model", model);
    m_FloorMesh->Draw();
}

} // namespace Engine
