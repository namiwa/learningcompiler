#include "common/common.h"
#include "window/window.hpp"
#include "shaders/shaders.hpp"


void fp() {
  std::cout << "render game state" << std::endl;
}

// dummy void function pointer for testing
void shaderWrapper(Shaders::Shader& shader) {
  std::cout << "running shaders" << std::endl;
  shader.use();
  shader.setFloat("someUniform", 1.0f);
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

  // figure out how to handle this hardcoded paths
  Shaders::Shader ourShader("./src/assets/shaders/vertex/triangle.vs", "./src/assets/shaders/fragment/triangle.fs");

  Window::Window *mainWindow = new Window::Window(800, 600, "namiwa main window!");
  // TODO: store in clean up func later.
  // mainWindow->displayWindow(&shaderWrapper, ourShader);
  delete mainWindow;
  mainWindow = nullptr;
  glfwTerminate();
  return 0;
}
