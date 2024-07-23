#include "player.h"
#include "graphics/renderer.h"
#include "physics/physics_body.h"
#include "physics/collider.h"
#include "resources/mesh.h"

#include <glm/vec3.hpp>

// Public functions 
/////////////////////////////////////////////////////////////////////////////////
Player* player_create(const glm::vec3& start_pos) {
  Player* player = new Player{};

  return player;
}

void player_destroy(Player* player) {
  if(!player) {
    return;
  }

  mesh_destroy(player->mesh);
  delete player;
}

void player_update(Player* player) {
  if(!player->is_active) {
    return;
  }
}

void player_render(Player* player) {
  if(!player->is_active) {
    return;
  }

  render_mesh(player->body->transform, player->mesh, glm::vec4(1.0f));
}
/////////////////////////////////////////////////////////////////////////////////
