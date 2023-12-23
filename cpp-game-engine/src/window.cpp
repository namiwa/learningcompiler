#include <map>
#include "window/window.hpp"
#include "shaders/shaders.hpp"
#include "utils/utils.hpp"

void Window::processExit(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, 1);
  }
}

void Window::windowErrorHandle(int error, const char *description)
{
  std::cerr << "Windowing Error: " << description << std::endl;
}

void Window::framebufferSizeHandle(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Window::Window::Window(int height, int width, const char *title)
{
  _window = nullptr;
  _title = title;
  _height = height;
  _width = width;

  std::cout << "Window init..." << std::endl;
  /* set error callback */

  /* create windowed mode window and its OpenGL context*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

  std::cout << "Window creation..." << std::endl;

  _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
  if (!_window)
  {
    std::cerr << "Window creation failed" << std::endl;
    return;
  }

  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window, framebufferSizeHandle);
  glfwSwapInterval(1);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!status)
  {
    std::cerr << "Failed to get init GLAD to OpenGL" << std::endl;
    return;
  }
  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER);             // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);               // version as a string
  const GLubyte *glsl = glGetString(GL_SHADING_LANGUAGE_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
  printf("GLSL version supported %s\n", glsl);
}

Window::Window::~Window() { glfwDestroyWindow(_window); }

void Window::Window::terminate()
{
  glfwDestroyWindow(_window);
}

void Window::Window::displayWindow(std::function<void(Shaders::Shader *)> fp, Shaders::Shader *shader)
{
  while (!glfwWindowShouldClose(_window))
  {
    // clean drawing surface for color and depth
    processExit(_window);
    printGlError();

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    printGlError();

    // call the game state render function below
    fp(shader);
    printGlError();

    glfwSwapBuffers(_window);
    glfwPollEvents();
    printGlError();
  }
  return;
}
