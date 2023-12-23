#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>

#include "file/file.hpp"
#include "shaders/shaders.hpp"
#include "utils/utils.hpp"

using namespace ghc;

std::string Shaders::setCharsFromFile(std::string &path)
{
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath))
    return "";
  if (File::pathIsDir(filepath))
    return "";
  return File::getFileAsString(filepath.string());
}

Shaders::Shader::Shader(std::string &vertexRoot, std::string &fragmentRoot,
                        std::vector<float> &verticesData)
{
  vertexContent = setCharsFromFile(vertexRoot);
  fragmentContent = setCharsFromFile(fragmentRoot);
  vertexSize = verticesData.size();
  vertices = verticesData;
  compile();
}

Shaders::Shader::~Shader()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
}

void Shaders::Shader::compile()
{
  // ------------------------------------
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char *vsource = vertexContent.c_str();
  glShaderSource(vertexShader, 1, &vsource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fsource = fragmentContent.c_str();
  glShaderSource(fragmentShader, 1, &fsource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glValidateProgram(shaderProgram);
  printGlError();

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Shaders::Shader::use()
{
  std::cout << "using shaders\n";
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Shaders::Shader::getId() { return shaderProgram; }

void Shaders::Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shaders::Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shaders::Shader::setFloat(const std::string &name, float value) const
{
  glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shaders::Shader::printInfo()
{
  std::cout << "shaderId: " << shaderProgram << "\n";
  std::cout << "vertexContent:\n"
            << vertexContent << "\n";
  std::cout << "fragmentContent:\n"
            << fragmentContent << "\n";
  std::cout << "vertexSize: " << vertices.size() << "\n";
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "vaoId: " << VAO << "\n";
  std::cout << "vboId: " << VBO << "\n";
}
