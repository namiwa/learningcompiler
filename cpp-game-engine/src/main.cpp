#include "shaders/shaders.hpp"
#include <iostream>

#if defined(__linux__)
#include <GLES/gl.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1
#include <OpenGL/OpenGL.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#else
std::cout << "Not supported non mac-os platform" << std::endl;
return 1;
#endif
#else
std::cout << "Un-supported platform!" << std::endl;
return 1;
#endif

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

/**
 * Main entry point for window. 
 */
int main(void)
{
    GLFWwindow *window;
    /* init library*/
    auto glfwInt = glfwInit();
    if (!glfwInt)
    {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }
    /* create windowed mode window and its OpenGL context*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(800, 600, "Hello World!", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Failed to init GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    int glStatus = gladLoadGL();
    glViewport(0, 0, 800, 600);
    if (!glStatus)
    {
        glfwTerminate();
        std::cout << "Failed to init GLAD OpenGL" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -1.0f, -0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2, // first triangle
        2, 3, 4  // second triangle
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    Shader ourShader("./assets/shaders/vertex/triangle.vs", "./assets/shaders/fragment/triangle.fs");
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        ourShader.use();
        ourShader.setFloat("someUniform", 1.0f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



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


