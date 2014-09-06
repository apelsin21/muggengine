muggengine
==========

Game Engine written in C/C++ primarily meant to be used through Lua.

Dependencies:

    SDL2
    
    ENet
    
    Bullet
    
    Assimp
    
    GLEW
    
    FreeType2
    
    FreeImage
    
    GLM

Requirements:

    Platform: Whatever x86 platforms SDL2 runs on.
    
    GPU: OpenGL 3.3 Core+, GLSL 3.30 Core+ (OpenGL ES isn't supported)

To build: 
Building is going to be a major hassle on anything except Linux.

Install all dependencies through your package manager and issue:
    
    cmake . 
    
    make
