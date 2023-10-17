#include "window/window.hpp"

// dummy void function pointer for testing
void fp() {}

/**
 * Main entry point for game hehe.
 */
int main(void) {
  // TODO: store in a init function later.
  auto glfwInt = glfwInit();
  if (!glfwInt) {
    std::cerr << "Failed to init GLFW" << std::endl;
  }
  auto mainWindow = Window::Window(800, 600, "namiwa main window!");
  mainWindow.displayWindow(&fp);
  mainWindow.terminate();
  mainWindow.~Window();
  // TODO: store in clean up func later.
  glfwTerminate();
  return 0;
}
