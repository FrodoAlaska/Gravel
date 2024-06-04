# TODO:
- Make a generic render batch structure to make creating different batches easier and more effcient
- Effcient text rendering
- Materials? 
- Load models 
- Model animations
- Minimal logger
- Some kind of arena allocater

# FIX 
- There's a problem when a font is freed.
- Make the bitmap returned from STB have a 4 bytes per pixel instead of 1. Just make the STB bitmap value as the alpha and leave the rest as 1s
- Problem with fonts still presists
- The kern and advance are fucked so need to fix that 
