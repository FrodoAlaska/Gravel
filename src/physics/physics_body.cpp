#include "physics_body.h"
#include "physics/collider.h"

#include <glm/glm.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_body_add_collider(PhysicsBody* body, const glm::vec3& scale, const std::string& id) {
  body->collider = new Collider{};
  body->collider->scale = scale;
  body->collider->min = glm::vec3(0.0f);
  body->collider->max = glm::vec3(1.0f);
  body->collider->id = id;
  body->collider->is_grounded = false;
  body->collider->body = body;

  collider_update_points(body->collider, body->position);
}
/////////////////////////////////////////////////////////////////////////////////
