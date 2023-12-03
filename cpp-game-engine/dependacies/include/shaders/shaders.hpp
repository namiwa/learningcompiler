#ifndef shaders_utils_h
#define shaders_utils_h

#include <cmath>
#include <string>
#include <vector>

#include <common/common.h>

namespace Shaders {
  std::string setCharsFromFile(std::string& path, const char* contents);

  class Shader {
    public:
      Shader(std::string vertexRoot, std::string fragmentRoot, float vertices[], unsigned int vertexLen);
      ~Shader();
      void use();
      // mistake below might be to not use GLuint...
      // proper mesh class will handle this vertices...
      unsigned int getId();
      void setBool(const std::string &name, bool value) const;
      void setInt(const std::string &name, int value) const;
      void setFloat(const std::string &name, float value) const;
      unsigned int vertexSize;
    private:
      void compile();
      const char* vertexContent;
      const char* fragmentContent;
      unsigned int shaderId;
      unsigned int vaoId;
      float* vertices;
  };
};

#endif // !shaders_utils_h
