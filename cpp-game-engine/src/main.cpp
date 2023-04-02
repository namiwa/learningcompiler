#include <OpenGL/OpenGL.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
} 


/**
 * within the hour, before i sleep, create a window in C++.
 */
int main(void)
{
    GLFWwindow* window;
    /* init library*/
    auto glfwInt = glfwInit();
    if (!glfwInt) {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }
    /* create windowed mode window and its OpenGL context*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(800, 600, "Hello World!", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to init GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    int glStatus = gladLoadGL();
    glViewport(0, 0, 800, 600);
    if (!glStatus) {
        glfwTerminate();
        std::cout << "Failed to init GLAD OpenGL" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
