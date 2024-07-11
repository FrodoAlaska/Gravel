#pragma once

#include "physics/physics_body.h"
#include "defines.h"

#include <glm/glm.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create(const glm::vec3& gravity);
void physics_world_destroy();
void physics_world_update(f64 timestep);

PhysicsBody* physics_world_add_body(const glm::vec3& pos, const bool dynamic, void* user_data, const bool active = true);
/////////////////////////////////////////////////////////////////////////////////
