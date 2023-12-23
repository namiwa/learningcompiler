#include <utils/utils.hpp>

template <class T> int getArrayLen(T arr[]) { return sizeof(arr) + 1; }

void printGlError() {
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error: " << error << std::endl;
  }
}
