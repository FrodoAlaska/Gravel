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
  body->torque = glm::vec3(0.0f);

  body->linear_velocity = glm::vec3(0.0f);
  body->angular_velocity = glm::vec3(0.0f);
  
  body->mass = desc.mass; 
  body->inverse_mass = desc.mass * -1;
  
  body->is_active = desc.is_active;
  body->user_data = desc.user_data;

  return body;
}

void physics_body_destroy(PhysicsBody* body) {
  if(!body) {
    return;
  } 

  delete body;
}

void physics_body_add_collider(PhysicsBody* body, ColliderType type, void* collider) {
  body->collider.type = type;
  body->collider.data = collider;
  body->collider.body = body;

  // Determining the size of the size of the collider 
  switch(type) {
    case COLLIDER_BOX: {
      BoxCollider* coll = (BoxCollider*)collider;
      transform_scale(&body->transform, coll->half_size * 2.0f);
    }
      break;
    case COLLIDER_SPHERE:
      SphereCollider* coll = (SphereCollider*)collider;
      transform_scale(&body->transform, glm::vec3(coll->radius)); // TODO: What?? Does this even work??
      break;
  }
}

void physics_body_apply_linear_force(PhysicsBody* body, const glm::vec3& force) {
  if(body->type == PHYSICS_BODY_STATIC) {
    return;
  }

  body->linear_velocity += force;
}

void physics_body_apply_angular_force(PhysicsBody* body, const glm::vec3& force) {
  if(body->type == PHYSICS_BODY_STATIC) {
    return;
  }

  // @TODO
}

void physics_body_apply_linear_impulse(PhysicsBody* body, const glm::vec3& force) {
  if(body->type == PHYSICS_BODY_STATIC) {
    return;
  }

  body->linear_velocity += force * body->inverse_mass;
}

void physics_body_apply_angular_impulse(PhysicsBody* body, const glm::vec3& force) {
  if(body->type == PHYSICS_BODY_STATIC) {
    return;
  }

  // @TODO
}
/////////////////////////////////////////////////////////////////////////////////
