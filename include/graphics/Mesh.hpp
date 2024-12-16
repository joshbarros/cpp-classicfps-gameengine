#pragma once

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace Engine {

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    Mesh();
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;
    void SetVertices(const std::vector<Vertex>& vertices);
    void SetIndices(const std::vector<unsigned int>& indices);

private:
    void SetupMesh();

    unsigned int m_VAO, m_VBO, m_EBO;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    bool m_IsInitialized = false;
};

} // namespace Engine
