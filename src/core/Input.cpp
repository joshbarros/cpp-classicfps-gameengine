#include "core/Input.hpp"

namespace Engine {

// Static member initialization
std::unordered_map<int, bool> Input::s_KeyStates;
std::unordered_map<int, bool> Input::s_PreviousKeyStates;
std::array<bool, GLFW_MOUSE_BUTTON_LAST> Input::s_MouseButtonStates = {};
double Input::s_MouseX = 0.0;
double Input::s_MouseY = 0.0;
double Input::s_LastMouseX = 0.0;
double Input::s_LastMouseY = 0.0;
bool Input::s_FirstMouse = true;
GLFWwindow* Input::s_Window = nullptr;

void Input::Initialize(GLFWwindow* window) {
    s_Window = window;
    
    // Set GLFW callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePositionCallback);
    
    // Enable raw mouse motion if available
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

bool Input::IsKeyPressed(int keyCode) {
    return s_KeyStates[keyCode] && !s_PreviousKeyStates[keyCode];
}

bool Input::IsKeyDown(int keyCode) {
    return s_KeyStates[keyCode];
}

bool Input::IsKeyReleased(int keyCode) {
    return !s_KeyStates[keyCode] && s_PreviousKeyStates[keyCode];
}

void Input::GetMousePosition(double& x, double& y) {
    x = s_MouseX;
    y = s_MouseY;
}

void Input::GetMouseDelta(double& x, double& y) {
    x = s_MouseX - s_LastMouseX;
    y = s_LastMouseY - s_MouseY; // Inverted Y for intuitive camera control
}

bool Input::IsMouseButtonPressed(int button) {
    return s_MouseButtonStates[button];
}

void Input::Update() {
    // Update previous key states
    s_PreviousKeyStates = s_KeyStates;
    
    // Update last mouse position
    s_LastMouseX = s_MouseX;
    s_LastMouseY = s_MouseY;
}

// Callback implementations
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        s_KeyStates[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        s_KeyStates[key] = false;
    }
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
        s_MouseButtonStates[button] = (action == GLFW_PRESS);
    }
}

void Input::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (s_FirstMouse) {
        s_LastMouseX = xpos;
        s_LastMouseY = ypos;
        s_FirstMouse = false;
    }
    
    s_MouseX = xpos;
    s_MouseY = ypos;
}

} // namespace Engine
