#include "common/common.h"
#include "window/window.hpp"

// dummy void function pointer for testing
void fp() {
  std::cout << "render game state" << std::endl;
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
  // TODO: store in clean up func later.
  mainWindow->displayWindow(&fp);
  delete mainWindow;
  mainWindow = nullptr;
  glfwTerminate();
  return 0;
}
