#include <GLFW/glfw3.h>
#include <iostream>

/**
 * within the hour, before i sleep, create a window in C++.
 */
int main(void)
{
    GLFWwindow* window;
    /* init library*/
    if (!glfwInit()) return -1;
    /* create windowed mode window and its OpenGL context*/
    window = glfwCreateWindow(640, 480, "Hello World!", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
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
