#include "window/window.hpp"

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
  _title = title;
  _height = height;
  _width = width;
}

Window::Window::~Window() { glfwDestroyWindow(_window); }

void Window::Window::Window::terminate() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Window::Window::displayWindow(void (*fp)()) {

  /* set error callback */
  glfwSetErrorCallback(windowErrorHandle);

  /* create windowed mode window and its OpenGL context*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  _window = glfwCreateWindow(_height, _width, _title, nullptr, nullptr);
  if (!_window) {
    std::cerr << "Failed to init GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(_window);
  glViewport(0, 0, _height, _width);

  int version = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); 
  if (version == 1) {
    printf("Failed to initialize OpenGL context\n");
    glfwTerminate();
    return;
  }

  glfwSetFramebufferSizeCallback(_window, framebufferSizeHandle);

  while (!glfwWindowShouldClose(_window)) {
    processExit(_window);
    glfwSwapBuffers(_window);
    fp();
    glfwPollEvents();
  }
  return;
}
