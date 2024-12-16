#include "core/Window.hpp"
#include <iostream>

namespace Engine {

Window::Window(const std::string& title, int width, int height)
    : m_Title(title)
    , m_Width(width)
    , m_Height(height)
    , m_Window(nullptr)
{
}

Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
}

bool Window::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    return true;
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

} // namespace Engine
