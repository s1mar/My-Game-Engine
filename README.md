# The Engine: Demo Breakout Clone
[GithubRepo](https://github.com/s1mar/My-Game-Engine)

I've always wanted to know what happens under the hood in commercial game engines. This is my attempt to build something of my own and learn the concepts in the process. For demonstration purposes, I've created a Breakout clone. A 2D game. Like in a commercial game engine, I've tried to divide the functionality into their respective modules or classes. For instance, GameController for encapsulating the game logic, and similar headers and classes for handling collisions, shaders, textures, resources, audio, particle system and rendering.
                                              
### Tech Stack

  - [OpenGl](https://www.opengl.org/) - For rendering.
  - [GLFW](https://www.glfw.org/) - It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
  - [GLEW](http://glew.sourceforge.net/) - It provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.
  - [SOIL2](https://github.com/SpartanJ/SOIL2) - A tiny C library used primarily for uploading textures into OpenGL.
  - [irrKlang](https://www.ambiera.com/irrklang/) - Sound engine and audio library which plays WAV, MP3, OGG, FLAC, MOD, XM, IT, S3M and more file formats.
  - [glm](https://glm.g-truc.net/0.9.9/index.html) - OpenGL Mathematics (GLM) is a header-only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.

### Concepts Explored
- How does rendering work with OpenGL?
- Shaders and working with textures.
- Orthographic projection and dealing with world space and normalized device coordinates.
- 2D Physics and collision resolution algorithms like AABB - AABB and AABB with a circle.
- Input Processing and events.
- Particle effects.
- Working with sound.
- Game Engine as a state machine.
- UI/UX.

### Demo Controls
- Press X or Esc anytime to quit.
- ← →   Arrow keys to move left and right.
- Space key to shoot the ball from the paddle.
- On the menu screen, press 1,2 or 3 to experience the respective levels.
  
### Screen-Shots
- ##### Menu Screen

    ![menu screen screenshot](https://i.imgur.com/scmMgi1.jpg)
    
- ##### Level 1

    ![level1 screen screenshot](https://i.imgur.com/MUbFGSd.jpg)
    
- ##### Level 2

    ![level2 screen screenshot](https://i.imgur.com/eGgVYwm.jpg)
    
- ##### Level 3

    ![level3 screen screenshot](https://i.imgur.com/zBrTdSp.jpg)

- ##### GameOver

    ![gameOver screen screenshot](https://i.imgur.com/vVtUEGQ.jpg)
    
### TODO
 - Experiment with Text Rendering.
 - Trying out other camera perspectives.
 - Maybe some networking features.

### Video Demo
[![Video Demo](http://img.youtube.com/vi/d8WLhm5T4W4/0.jpg)](http://www.youtube.com/watch?v=d8WLhm5T4W4 "Video Demo")
 

    
