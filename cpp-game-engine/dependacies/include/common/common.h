#ifndef common_hpp
#define common_hpp

#if defined(__linux__)
#include <GLES/gl.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1
#include <OpenGL/OpenGL.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#else
std::cout << "Not supported non mac-os platform" << std::endl;
return 1;
#endif
#else
std::cout << "Un-supported platform!" << std::endl;
return 1;
#endif

#endif // !common_hpp

