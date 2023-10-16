#include "window/window.hpp"
#include "GLFW/glfw3.h"

void Window::processExit(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}



