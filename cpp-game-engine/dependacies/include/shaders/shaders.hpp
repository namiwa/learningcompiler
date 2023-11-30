#ifndef shaders_utils_h
#define shaders_utils_h

#include <string>
#include <vector>

#include <common/common.h>

namespace Shaders {
  std::string setCharsFromFile(std::string& path, const char* contents);
  class Shader {
    public:
      Shader(std::string vertexRoot, std::string fragmentRoot);
      ~Shader();
      void use();
      GLint* getId();
      void setBool(const std::string &name, bool value) const;
      void setInt(const std::string &name, int value) const;
      void setFloat(const std::string &name, float value) const;
    private:
      void compile();
      const char* vertexContent;
      const char* fragmentContent;
      GLint* shaderId;
  };
};

#endif // !shaders_utils_h
