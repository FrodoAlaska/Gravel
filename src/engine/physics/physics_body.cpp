#include "physics_body.h"
#include "defines.h"
#include "math/transform.h"
#include "physics/collider.h"

#include <glm/vec3.hpp>

// Public functions 
/////////////////////////////////////////////////////////////////////////////////
PhysicsBody* physics_body_create(const PhysicsBodyDesc& desc) {
  PhysicsBody* body = new PhysicsBody{};
  
  transform_create(&body->transform, desc.position);
  body->type = desc.type;
  body->force = glm::vec3(0.0f);
  body->acceleration = glm::vec3(0.0f);
  body->linear_velocity = glm::vec3(0.0f);
  body->angular_velocity = glm::vec3(0.0f);
  body->mass = desc.mass; 
  body->inverse_mass = -desc.mass;
  body->is_active = desc.is_active;

  return body;
}

void physics_body_destroy(PhysicsBody* body) {
  delete body;
}

void physics_body_add_collider(PhysicsBody* body, ColliderType type, void* collider) {
  body->collider.type = type;
  body->collider.data = collider;
}

void physics_body_apply_force(PhysicsBody* body, const glm::vec3& force) {
  body->force += force;
}
/////////////////////////////////////////////////////////////////////////////////
