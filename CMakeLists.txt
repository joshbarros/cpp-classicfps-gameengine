cmake_minimum_required(VERSION 3.10)

# Set C++ compiler to Clang
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(ClassicFPSEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add debug symbols
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add ImGui
add_subdirectory(vendor/imgui)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    /opt/homebrew/include
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    vendor/imgui
)

# Link directories
link_directories(
    /opt/homebrew/lib
)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

# Create executable
add_executable(ClassicFPSEngine
    src/main.cpp
    src/core/Engine.cpp
    src/core/Input.cpp
    src/core/Window.cpp
    src/graphics/Camera.cpp
    src/graphics/Mesh.cpp
    src/graphics/Shader.cpp
    src/physics/PhysicsSystem.cpp
    src/player/PlayerController.cpp
    ${SOURCES}
)

# Link libraries
target_link_libraries(ClassicFPSEngine 
    OpenGL::GL
    glfw
    GLEW::GLEW
    imgui
)

# Set include directories for the target
target_include_directories(ClassicFPSEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
