#include "physics_world.h"
#include "core/event.h"
#include "physics/collider.h"
#include "physics/collision_data.h"
#include "physics/physics_body.h"

#include <glm/vec3.hpp>

#include <vector>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  std::vector<PhysicsBody*> bodies;
  std::vector<CollisionData> collisions;

  glm::vec3 gravity;
};

static PhysicsWorld* world;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void check_collisions() {
  for(auto& body1 : world->bodies) {
    if(!body1->is_active) {
      continue;
    }

    for(auto& body2 : world->bodies) {
      if(!body2->is_active) {
        continue;
      }

      // Make sure to not check collisions with the same body
      if(body1->collider->id == body2->collider->id) {
        continue;
      }      

      CollisionData data;
      if(collider_is_colliding(body1->collider, body2->collider, &data)) {
        world->collisions.push_back(data);
        event_dispatch(EVENT_ENTITY_COLLISION, EventDesc{.coll_data = data});
      }
    }
  }
}

static void resolve_collisions() {
  for(auto& coll : world->collisions) {
    if(coll.coll1->body->is_dynamic) {
      coll.coll1->body->position += (-coll.normal * coll.depth); 
      coll.coll1->body->velocity = glm::vec3(0.0f); 

      if(coll.normal.y == 1.0f) {
        coll.coll1->is_grounded = true;
      }
    }
    
    if(coll.coll2->body->is_dynamic) {
      coll.coll2->body->position += (coll.normal * coll.depth); 
      coll.coll2->body->velocity = glm::vec3(0.0f); 

      if(coll.normal.y == 1.0f) {
        coll.coll2->is_grounded = true;
      }
    }
  }

  if(!world->collisions.empty()) {
    world->collisions.clear();
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create(const glm::vec3& gravity) {
  world          = new PhysicsWorld{};
  world->gravity = gravity;
}

void physics_world_destroy() {
  for(auto& body : world->bodies) {
    delete body;
  }

  delete world;
}

void physics_world_update(f64 timestep) {
  for(auto& body : world->bodies) {
    // No need to move the body at all if it's static or inactive
    if(!body->is_dynamic || !body->is_active) {
      continue;
    }

    body->force = world->gravity; 
    
    body->velocity += body->force;
    body->position += body->velocity * (f32)timestep;

    collider_update_points(body->collider, body->position);
  }

  check_collisions();
  resolve_collisions();
}

PhysicsBody* physics_world_add_body(const glm::vec3& pos, const bool dynamic, void* user_data, const bool active) {
  PhysicsBody* body = new PhysicsBody{};
  body->position = pos;
  body->velocity = glm::vec3(0.0f);
  body->force = glm::vec3(0.0f);
  body->collider = nullptr;
  body->is_active = active; 
  body->is_dynamic = dynamic;
  body->user_data = user_data;

  world->bodies.push_back(body);
  return body;
}
/////////////////////////////////////////////////////////////////////////////////
