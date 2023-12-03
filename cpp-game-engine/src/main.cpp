#include "common/common.h"
#include "window/window.hpp"
#include "shaders/shaders.hpp"


void fp(Shaders::Shader& shader) {
  std::cout << "render game state" << std::endl;

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL Error: " << error << std::endl;
  }

  char infoLog[512];
  glGetProgramInfoLog(shader.getId(), 512, NULL, infoLog);
  std::cout << "shader error: " << infoLog << std::endl;
  std::cout << "vertexArray size: " << shader.vertexSize << std::endl;
}

// dummy void function pointer for testing
void shaderWrapper(Shaders::Shader& shader) {
  std::cout << "running shaders" << std::endl;
  shader.use();
  fp(shader);
}

/**
 * Main entry point for game hehe.
 */
int main(void) {
  // TODO: store in a init function later.
  auto glfwInt = glfwInit();
  if (!glfwInt) {
    std::cerr << "Failed to init GLFW" << std::endl;
  }

  Window::Window *mainWindow = new Window::Window(800, 600, "namiwa main window!");
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  }; 
  Shaders::Shader ourShader("./src/assets/shaders/vertex/triangle.vs", "./src/assets/shaders/fragment/triangle.fs", vertices, 9);
  // TODO: store in clean up func later.
  mainWindow->displayWindow(&shaderWrapper, ourShader);
  delete mainWindow;
  mainWindow = nullptr;
  glfwTerminate();
  return 0;
}
