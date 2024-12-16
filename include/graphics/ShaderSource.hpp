#pragma once

namespace Engine {

const char* const DEFAULT_VERTEX_SHADER = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    
    uniform mat4 projection;
    uniform mat4 view;
    
    out vec3 FragColor;
    out vec3 FragPos;
    
    void main() {
        FragPos = aPos;
        FragColor = aColor;
        gl_Position = projection * view * vec4(aPos, 1.0);
    }
)";

const char* const DEFAULT_FRAGMENT_SHADER = R"(
    #version 330 core
    in vec3 FragColor;
    in vec3 FragPos;
    
    out vec4 FinalColor;
    
    void main() {
        // Basic lighting calculation
        vec3 lightPos = vec3(2.0, 2.0, 2.0);
        vec3 lightColor = vec3(1.0, 1.0, 1.0);
        
        // Ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
        
        // Diffuse
        vec3 norm = normalize(FragPos);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        
        // Combine
        vec3 result = (ambient + diffuse) * FragColor;
        FinalColor = vec4(result, 1.0);
    }
)";

} // namespace Engine
