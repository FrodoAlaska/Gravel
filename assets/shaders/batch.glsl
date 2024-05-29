@type vertex 
#version 460 core 

// Layouts 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTextureCoords;
layout (location = 3) in float aTextureIndex;

// Outputs
out VS_OUT 
{
  vec4 out_color; 
  vec2 tex_coords;
  float tex_index;
} vs_out;

void main() 
{
  vs_out.out_color  = aColor;
  vs_out.tex_coords = aTextureCoords;
  vs_out.tex_index  = aTextureIndex;

  gl_Position = vec4(aPos, 1.0f);
}

@type fragment
#version 460 core 

// Outputs 
out vec4 frag_color;

// Inputs
in VS_OUT 
{
  vec4 out_color; 
  vec2 tex_coords;
  float tex_index;
} fs_in;

// Uniforms
uniform sampler2D u_textures[32];

void main() 
{
  int index = int(fs_in.tex_index);
  frag_color = texture(u_textures[index], fs_in.tex_coords) * fs_in.out_color;
}
