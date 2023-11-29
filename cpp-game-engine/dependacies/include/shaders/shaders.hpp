#ifndef shaders_utils_h
#define shaders_utils_h

#include <string>
#include <vector>

#include <common/common.h>

namespace Shaders {
  void setCharsFromFile(std::string path, const char* contents);
  class Shader {
    public:
      Shader(std::string vertexRoot, std::string fragmentRoot);
      ~Shader();
      void use();
      void compile();
      int getId();
    private:
      const char* vertexContent;
      const char* fragmentContent;
  };
};

#endif // !shaders_utils_h
