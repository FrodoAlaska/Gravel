# TODO:
- Don't flip the pixels when loading STB image and instead flip the uvs
- Test the new sound stuff
- Effcient text rendering
- Make a generic render batch structure to make creating different batches easier and more effcient
- Materials? 
- Load models 
- Model animations
- Minimal logger
- Some kind of arena allocater

# FIX 
- Textures no work
- Make the bitmap returned from STB have a 4 bytes per pixel instead of 1. Just make the STB bitmap value as the alpha and leave the rest as 1s
- Problem with fonts still presists
- The kern and advance are fucked so need to fix that 
