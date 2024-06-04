# TODO:
- Move the texture and font to a seperate folder called "resources" because that's what they are
- Resource manager
- A way to setup the engine 
- Make a generic render batch structure to make creating different batches easier and more effcient
- Effcient text rendering
- Materials? 
- Load models 
- Model animations
- Minimal logger
- Some kind of arena allocater

# FIX 
- Problem with fonts still presists
- The kern and advance are fucked so need to fix that 
- Make the bitmap returned from STB have a 4 bytes per pixel instead of 1. Just make the STB bitmap value as the alpha and leave the rest as 1s
