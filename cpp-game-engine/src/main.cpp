#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * within the hour, before i sleep, create a window in C++.
 */
int main(void)
{
    GLFWwindow* window;
    /* init library*/
    auto glfwInt = glfwInit();
    if (!glfwInt) return -1;
    /* create windowed mode window and its OpenGL context*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(640, 480, "Hello World!", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

  // c++: user memory management
  /**
  there are 2 types of memory, stack and heap.
  stack is static, allocated at run time.
  
  stack faster than heap.
  stack is automatically cleared when scope is left.
  reference --> safe operation meaning that it points to some data
  ie it can never point to nothing / nullptr
  by default, everything is pass by value
  */
