#include "physics/PhysicsSystem.hpp"

namespace Engine {

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::Update(float deltaTime) {
    // Update physics simulation
    for (auto& collider : m_Colliders) {
        if (!collider.isStatic) {
            // Apply gravity
            collider.position.y += GRAVITY * deltaTime;
        }
    }
}

void PhysicsSystem::AddCollider(const Collider& collider) {
    m_Colliders.push_back(collider);
}

bool PhysicsSystem::CheckCollision(const glm::vec3& position, const glm::vec3& size) const {
    // Simple AABB collision detection
    for (const auto& collider : m_Colliders) {
        bool collisionX = position.x + size.x >= collider.position.x && 
                         collider.position.x + collider.size.x >= position.x;
        bool collisionY = position.y + size.y >= collider.position.y && 
                         collider.position.y + collider.size.y >= position.y;
        bool collisionZ = position.z + size.z >= collider.position.z && 
                         collider.position.z + collider.size.z >= position.z;
        
        if (collisionX && collisionY && collisionZ) {
            return true;
        }
    }
    return false;
}

} // namespace Engine
