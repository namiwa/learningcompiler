#include <GLFW\glfw3.h>
#include <iostream>

/**
 * within the hour, before i sleep, create a window in C++.
 */

int main(int argc, char * argv[])
{
    std::cout << "Hello World" << endl;
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
