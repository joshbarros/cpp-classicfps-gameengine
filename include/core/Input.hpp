#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <array>

namespace Engine {

class Input {
public:
    static void Initialize(GLFWwindow* window);
    
    // Keyboard input
    static bool IsKeyPressed(int keyCode);
    static bool IsKeyDown(int keyCode);
    static bool IsKeyReleased(int keyCode);
    
    // Mouse input
    static void GetMousePosition(double& x, double& y);
    static void GetMouseDelta(double& x, double& y);
    static bool IsMouseButtonPressed(int button);
    
    // Update state
    static void Update();

private:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    
    static std::unordered_map<int, bool> s_KeyStates;
    static std::unordered_map<int, bool> s_PreviousKeyStates;
    static std::array<bool, GLFW_MOUSE_BUTTON_LAST> s_MouseButtonStates;
    static double s_MouseX, s_MouseY;
    static double s_LastMouseX, s_LastMouseY;
    static bool s_FirstMouse;
    static GLFWwindow* s_Window;
};

} // namespace Engine
