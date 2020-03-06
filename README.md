# My Game Engine
  My attempt at building a custom game engine.
# New Features!
  - Uses a single GL_ARRAY type buffer to hold both position and color data for a primitive.
  - Primitives of the same type(for eg, triangles) share some vertices, element buffer is used and glDrawElements is used to draw the primitives.
  - Basic Vertex and Fragment shaders. 
  - Basic translation using a Uniform variable in the vertex shader
  - Shows FPS
  - Wireframe can be seen/unseen by pressing the "L" key. The window can also be closed using the "end" key.
  - Window resizing works, the glViewport is set everytime the frame buffer size changes.