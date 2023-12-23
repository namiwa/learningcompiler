#include "common/common.h"
#include "shaders/shaders.hpp"
#include "utils/utils.hpp"
#include "window/window.hpp"
#include <cstring>

// dummy void function pointer for testing
void shaderWrapper(Shaders::Shader *shader) {
  std::cout << "running shaders" << std::endl;
  if (!shader) {
    std::cout << "skipping empty shader\n";
    return;
  }
  shader->use();
  printGlError();
}

/**
 * Main entry point for game hehe.
 */
int main2(void) {
  // TODO: store in a init function later.
  auto glfwInt = glfwInit();
  if (!glfwInt) {
    std::cerr << "Failed to init GLFW" << std::endl;
    return 1;
  }

	// TODO: engine objects
  Window::Window *mainWindow =
      new Window::Window(800, 600, "namiwa main window!");
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  Shaders::Shader *ourShader = new Shaders::Shader(
      "./src/assets/shaders/vertex/triangle.glsl",
      "./src/assets/shaders/fragment/triangle.glsl", vertices, 9);

	// TODO: drawing displaying
  mainWindow->displayWindow(&shaderWrapper, ourShader);

	// TODO: consolidate clean up method
  delete mainWindow;
  mainWindow = nullptr;
  delete ourShader;
  ourShader = nullptr;
  glfwTerminate();
  return 0;
}
