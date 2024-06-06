# TODO:
- Effcient text rendering
- Custom enums for the opengl types so that I don't have to include <glad/gl.h> everywhere
- Make a generic render batch structure to make creating different batches easier and more effcient
- Materials? 
- Load models 
- Model animations
- Minimal logger
- Some kind of arena allocater

# FIX 
- Make the bitmap returned from STB have a 4 bytes per pixel instead of 1. Just make the STB bitmap value as the alpha and leave the rest as 1s
- Problem with fonts still presists
