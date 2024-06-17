# TODO:
- Add models to resources

# LATER TODO:
- Model animations
- Minimal logger
- Physics
- Some kind of arena allocater

# FIX: 
- The each mesh has a specific material index in the material array. The correct material needs to be used with the appropriate mesh
- Mouse position stuff - perhaps you'll need to change it into the projection matrix when moving the camera
- The 2D renderer and 3D renderer don't work so well together
- Texts get fucked with long strings for some reason - maybe reaching the texture limit?
- The 2D renderer needs a whole rewrite. Perhaps a 'begin_vertex' and 'end_vertex' functions so I don't have to redo the whole thing again??
