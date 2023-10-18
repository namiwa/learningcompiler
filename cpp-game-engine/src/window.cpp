#include "window/window.hpp"
#include "GLFW/glfw3.h"

void Window::processExit(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

void Window::windowErrorHandle(int error, const char *description) {
  std::cerr << "Windowing Error: " << description << std::endl;
}

void Window::framebufferSizeHandle(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

Window::Window::Window(int height, int width, const char *title) {
  _window = nullptr;
  _title = title;
  _height = height;
  _width = width;
}

Window::Window::~Window() { glfwDestroyWindow(_window); }

void Window::Window::terminate() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Window::Window::displayWindow(std::function<void()> fp) {
  std::cout << "Window init..." << std::endl;
  /* set error callback */
  glfwSetErrorCallback(windowErrorHandle);

  /* create windowed mode window and its OpenGL context*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  
  std::cout << "Window creation..." << std::endl;

  _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
  if (!_window) {
    std::cerr << "Window creation failed" << std::endl;
    return;
  }

  glfwMakeContextCurrent(_window);
  int status = gladLoadGL();
  if (!status) {
    std::cerr << "Failed to get init GLAD to OpenGL" << std::endl;
    return;
  }

  glViewport(0, 0, _width, _height);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(_window)) {
    // call the game state render function below
    glfwGetFramebufferSize(_window, &_width, &_height);
    fp();

    processExit(_window);
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }

  return;
}
