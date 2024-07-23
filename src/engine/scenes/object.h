#pragma once

#include "physics/physics_body.h"
#include "physics/collider.h"
#include "resources/mesh.h"

#include <glm/vec3.hpp>

// Object
/////////////////////////////////////////////////////////////////////////////////
/*
 * An object is just a generic structure of what a, perhaps, static 
 * prop/entity/object in the world might have. This can be customized 
 * further or dumped down even if needed. The 'Scene' struct has an 
 * array of these objects. 
 *
 * This is perhaps not the best generic way of making an object in this engine, 
 * but it's the way that I usually make these objects. And this is, again, stricly 
 * _my_ way of making a game. Feel free to edit this however you want, though.
 */
struct Object {
  PhysicsBody* body; 
  BoxCollider collider;
  Mesh* mesh;

  bool is_active;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Object* object_create(const glm::vec3& scale, const PhysicsBodyDesc desc, const bool active = true);
void object_destroy(Object* obj);
void object_render(Object* obj);
/////////////////////////////////////////////////////////////////////////////////
