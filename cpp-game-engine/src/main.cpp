#include <iostream>
#include <string>
#include <vector>

#include "common/common.h"
#include "window/window.hpp"
#include "shaders/shaders.hpp"
#include "utils/utils.hpp"

std::string vpath = "./src/assets/shaders/vertex/triangle.glsl";
std::string fpath = "./src/assets/shaders/fragment/triangle.glsl";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    Window::Window *window = new Window::Window(800, 600, "namiwa");

    // build and compile our shader program
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };
    Shaders::Shader *shader = new Shaders::Shader(vpath, fpath, vertices);

    // render loop
    // -----------
    window->displayWindow([](Shaders::Shader *s)
                          { 
                            s->use();
                            printGlError(); },
                          shader);
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete window;
    window = nullptr;
    delete shader;
    shader = nullptr;
    glfwTerminate();
    return 0;
}
