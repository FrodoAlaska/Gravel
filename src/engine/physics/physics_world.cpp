#include "physics_world.h"
#include "math/transform.h"
#include "physics/physics_body.h"
#include "defines.h"

#include <glm/vec3.hpp>

#include <vector>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  std::vector<PhysicsBody*> bodies;
  glm::vec3 gravity;
};

static PhysicsWorld* s_world;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void check_collisions() {
  // TODO
}

static void resolve_collisions() {
  // TODO
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create(const glm::vec3& gravity) {
  s_world = new PhysicsWorld{}; 
  s_world->gravity = gravity;
}

void physics_world_destroy() {
  for(auto& body : s_world->bodies) {
    physics_body_destroy(body);
  }
  s_world->bodies.clear();

  delete s_world;
}

void physics_world_set_gravity(const glm::vec3& gravity) {
  s_world->gravity = gravity;
}

void physics_world_update(f32 dt) {
  /*
   * NOTE:
   * This physics system uses the Semi-Implicit Euler integration system. 
   * It is perhaps not the best/accurate integration out there. However, 
   * it does satisfy the needs of a real-time game physics simulation. 
   * It's fast, easy to use, and accurate enough for game simulations. 
   *
   * Here's a link for info: 
   * https://en.wikipedia.org/wiki/Semi-implicit_Euler_method
   */

  for(auto& body : s_world->bodies) {
    // Inactive and static bodies do not need to be updated 
    if(!body->is_active || body->type == PHYSICS_BODY_STATIC) {
      continue;
    }

    // Add the most important force to the body 
    body->force += s_world->gravity;

    // Semi-Implicit Euler in effect
    body->acceleration = body->force * body->inverse_mass;
    body->linear_velocity += body->acceleration * dt;
    body->transform.position += body->linear_velocity * dt;

    // Moving the body by the new position/displacment
    transform_translate(&body->transform, body->transform.position); 

    // Clear all forces accumulated this frame
    body->force = glm::vec3(); 
  } 

  check_collisions();
  resolve_collisions();
}

PhysicsBody* physics_world_add_body(const PhysicsBodyDesc& desc) {
  PhysicsBody* body = physics_body_create(desc);
  s_world->bodies.push_back(body);
  
  return body;
}
/////////////////////////////////////////////////////////////////////////////////
