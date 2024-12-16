#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Engine {

struct Collider {
    glm::vec3 position;
    glm::vec3 size;
    bool isStatic;
};

class PhysicsSystem {
public:
    PhysicsSystem();
    
    void Update(float deltaTime);
    void AddCollider(const Collider& collider);
    bool CheckCollision(const glm::vec3& position, const glm::vec3& size) const;
    
    static constexpr float GRAVITY = -9.81f;
    
private:
    std::vector<Collider> m_Colliders;
};

} // namespace Engine
