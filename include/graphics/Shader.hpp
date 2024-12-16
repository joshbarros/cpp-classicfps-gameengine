#pragma once

#include "math/Mat4.hpp"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine {

class Shader {
public:
    Shader();
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    bool LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    void Use() const;

    // Uniform setters
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetMat2(const std::string& name, const glm::mat2& value) const;
    void SetMat3(const std::string& name, const glm::mat3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;
    
private:
    bool CompileShader(unsigned int& shader, const std::string& source, unsigned int type);
    bool LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);
    std::string ReadFile(const std::string& filePath);
    
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_UniformLocations;
};

} // namespace Engine
