#ifndef shaders_utils_h
#define shaders_utils_h

#include <string>
#include <vector>

#include <common/common.h>

namespace Shaders {
  const char* getCharsFromFile(std::string path);
  void processShaderChar(const char* contents);
  class Shader {
    public:
      Shader(std::string vertexRoot, std::string fragmentRoot);
      void use(int id);
      std::vector<unsigned int> getIds();
    private:
      std::vector<unsigned int> ids;
  };
};

#endif // !shaders_utils_h
