# Learning to build game engine from scratch


## Installation

ensure running either on linux (or windows wsl) or macos.
todo: run install script
run platform build script
window should open and game should be running on said screen.


## Attributions
* GLFW/GLAD windowing: 
  - https://github.com/Dav1dde/glad?tab=readme-ov-file
  - https://glad.dav1d.de/
* filesystem: https://github.com/gulrak/filesystem


## Motivation
This documents the beginning of learning game development from scratch. Starting with:

- OpenGL in C++ (restrict to 2D environment)
- Understanding how physics / physics engines work (for 2D space)
- Asset loading (textures & audio)
- tying it all together with an entity control system (somehow??)


## Supported Platforms

### MacOS
Get the required osx developer tool chain from xcode

### Ubuntu (WSL)
install the `freeglut3-dev` package, basically the basics for OpenGl, Glad & GLFW support!


## Debugging

with the compiled game, there's valgrind to measure memory usage and leaks, and running
the following gdb to step through the program binary
```bash
sudo gdb ./game_app
```

## References

https://learnopengl.com/Getting-started/Hello-Triangle

https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html

https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

https://david-delassus.medium.com/a-short-introduction-to-entity-component-system-in-c-with-entt-330b7def345b

https://www.codingwiththomas.com/blog/an-entity-component-system-from-scratch 

https://austinmorlan.com/posts/entity_component_system/
