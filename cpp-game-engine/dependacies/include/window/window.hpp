#ifndef window_hpp
#define window_hpp

#include "GLFW/glfw3.h"

namespace Window {
  void processExit(GLFWwindow *window);
  void framebufferSize(GLFWwindow *window);
  void windowErrorHandle(int error, const char *description);
  
  class Window {
    private:
      GLFWwindow *window;
    public:
      Window();
      ~Window();
      void displayWindow(void (*fp)(void));
      void terminate();
  };
};

#endif // !window_hpp
