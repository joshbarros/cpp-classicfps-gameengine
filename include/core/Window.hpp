#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Engine {

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool Initialize();
    void SwapBuffers();
    bool ShouldClose() const;
    
    GLFWwindow* GetNativeWindow() const { return m_Window; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    GLFWwindow* m_Window;
    std::string m_Title;
    int m_Width;
    int m_Height;
};

} // namespace Engine
