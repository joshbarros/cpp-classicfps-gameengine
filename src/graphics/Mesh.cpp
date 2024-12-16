#include "graphics/Mesh.hpp"
#include <GL/glew.h>

namespace Engine {

Mesh::Mesh()
    : m_VAO(0)
    , m_VBO(0)
    , m_EBO(0)
    , m_IsInitialized(false) {
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_VAO(0)
    , m_VBO(0)
    , m_EBO(0)
    , m_Vertices(vertices)
    , m_Indices(indices)
    , m_IsInitialized(false) {
    SetupMesh();
}

Mesh::~Mesh() {
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
    }
    if (m_VBO != 0) {
        glDeleteBuffers(1, &m_VBO);
    }
    if (m_EBO != 0) {
        glDeleteBuffers(1, &m_EBO);
    }
}

void Mesh::SetVertices(const std::vector<Vertex>& vertices) {
    m_Vertices = vertices;
    if (!m_Indices.empty()) {
        SetupMesh();
    }
}

void Mesh::SetIndices(const std::vector<unsigned int>& indices) {
    m_Indices = indices;
    if (!m_Vertices.empty()) {
        SetupMesh();
    }
}

void Mesh::SetupMesh() {
    if (m_IsInitialized) {
        // Clean up previous buffers
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    // Create buffers/arrays
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Load data into vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    // Load data into element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
    m_IsInitialized = true;
}

void Mesh::Draw() const {
    if (!m_IsInitialized) {
        return;
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace Engine
