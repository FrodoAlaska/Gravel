#include "physics_world.h"
#include "core/event.h"
#include "math/transform.h"
#include "physics/collider.h"
#include "physics/collision_data.h"
#include "physics/physics_body.h"
#include "defines.h"

#include <glm/vec3.hpp>

#include <vector>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  glm::vec3 gravity;
  
  std::vector<PhysicsBody*> bodies;
  std::vector<CollisionData> collisions;
};

static PhysicsWorld* s_world;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void check_collisions() {
  for(u32 i = 0; i < s_world->bodies.size(); i++) {
    // Skip inactive bodies
    PhysicsBody* body_a = s_world->bodies[i];
    if(!body_a->is_active) {
      continue;
    }

    for(u32 j = i + 1; j < s_world->bodies.size(); j++) {
      // Don't check for the same bodies 
      if(i == j) {
        continue;
      }

      PhysicsBody* body_b = s_world->bodies[j];
      if(!body_b->is_active) {
        continue;
      }

      CollisionData data = collider_colliding(&body_a->collider, &body_a->transform, &body_b->collider, &body_b->transform);
      
      // When a collision happens, an even gets dispatched to whoever cares to listen. 
      // The collision data also gets added to a vector to be resolved later.
      if(data.collision_point.has_collided) {
        event_dispatch(EVENT_ENTITY_COLLISION, EventDesc{.coll_data = data});
        s_world->collisions.push_back(data);
      }
    }
  }
}

static void resolve_collisions() {
  // for(auto& collision : s_world->collisions) {
  //   
  // }
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
