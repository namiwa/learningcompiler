#ifndef window_hpp
#define window_hpp

#include <iostream>

#include "common/common.h"

namespace Window {
  void processExit(GLFWwindow *window);
  void framebufferSizeHandle(GLFWwindow *window, int width, int height);
  void windowErrorHandle(int error, const char *description);
  
  class Window {
    private:
      GLFWwindow *_window;
      const char* _title;
      int _height;
      int _width;
    public:
      Window(int height, int width, const char *title);
      ~Window();
      void displayWindow(void (*fp)(void));
      void terminate();
  };
};

#endif // !window_hpp
