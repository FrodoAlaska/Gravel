#pragma once

#include "resources/mesh.h"
#include "resources/texture.h"
#include "resources/font.h"
#include "math/vertex.h"
#include "defines.h"

#include <string>
#include <vector>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
// The initial initialization of the resource manager. The given 'res_path' will be 
// prefixed to any subsequent 'resources_add_*' functions, so as not to repeat the 
// same path over and over. Do note, however, the resource manager will allocate memory 
// on the heap. Though, it will be responsible for the deallocations as well. That is 
// the purpose of the 'resources_shutdown' functions
void resources_init(const std::string res_path);
void resources_shutdown();

// Adding resources 
// The following functions will take an 'id' string and the respectful parametars for each resource. 
// It then will add the newly created resource in the map with the equivalent ID. It will then 
// return the specified resource.
//
// NOTE: The path that is passed to the functions should omit the initial resource path, as 
// that is given initially when the resource manager is initialized. For example, if a texture is 
// at "res/textures/texture.png" then the "res/" should be removed. Therefore, it should be "textures/texture.png".
Texture* resources_add_texture(const std::string& id, const std::string& path);
Texture* resources_add_texture(const std::string& id, i32 width, i32 height, TextureFormat format, void* pixels);
Font* resources_add_font(const std::string& path, const std::string& id);
Mesh* resources_add_mesh(const std::string& id);
Mesh* resources_add_mesh(const std::string& id, const std::vector<Vertex3D>& vertices, const std::vector<u32>& indices);

// Returning resources 
// These functions will return the resource that is specified by the 'id'. 
// These functions will return a 'nullptr' if the resource was not found.
Texture* resources_get_texture(const std::string& id);
Font* resources_get_font(const std::string& id);
Mesh* resources_get_mesh(const std::string& id);

// Removing resources
// Removes the specified resource from the resource manager's map. 
// These functions will return a 'true' if the resource is found and successfully removed 
// and 'false' otherwise. 
// NOTE: These functions also unload the resources before removing the resource from the manager. 
// Therefore, please do be careful when using these functions.
bool resources_remove_texture(const std::string& id);
bool resources_remove_font(const std::string& id);
bool resources_remove_mesh(const std::string& id);
/////////////////////////////////////////////////////////////////////////////////
