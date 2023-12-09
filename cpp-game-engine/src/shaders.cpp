#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>

#include "shaders/shaders.hpp"
#include "file/file.hpp"

using namespace ghc;

std::string Shaders::setCharsFromFile(std::string& path) {
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath)) return "";
  if (File::pathIsDir(filepath)) return "";
  return File::getFileAsString(filepath.string());
}

Shaders::Shader::Shader(std::string vertexRoot, std::string fragmentRoot, float verticesData[], unsigned int vertexLen) {
  vertexContent = setCharsFromFile(vertexRoot);
  fragmentContent = setCharsFromFile(fragmentRoot);
  vertexSize = vertexLen;
  vertices = (float *) std::malloc(vertexLen * sizeof(float));
  for (int i = 0; i < vertexLen; i++) {
    std::cout << "before\n";
    std::cout << vertices[i] << std::endl;
    vertices[i] = verticesData[i];
    std::cout << "after\n";
    std::cout << vertices[i] << std::endl;
  }
  compile();
}

Shaders::Shader::~Shader() {
  if (glIsProgram(shaderId)) {
    glDeleteProgram(shaderId);
  }
  free(vertices);
  glDeleteBuffers(1, &vboId);
  glDeleteVertexArrays(1, &vaoId);
}

void Shaders::Shader::compile() {
  std::cout << "compling shaders\n";
  GLint vertex, fragment;
  int success;
  char infoLog[512];

  // add vertices to VAO
  glGenVertexArrays(1, &vaoId);
  glGenBuffers(1, &vboId); 
  
  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  // compile vertexShader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  std::cout << "compiling vertexContent: " << vertexContent << std::endl;
  const char* vt = vertexContent.c_str();
  glShaderSource(vertex, 1, &vt, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error vertex shader compilation error\n" << infoLog << std::endl;
  }
  std::cout << "vertex shader created " << vertex << "\n";

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  std::cout << "compiling fragmentContent: " << fragmentContent << std::endl;
  const char* ft = fragmentContent.c_str();
  glShaderSource(fragment, 1, &ft, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "Error fragment shader compilation error\n" << infoLog << std::endl;
  }
  std::cout << "fragment shader created " << fragment << "\n";

  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertex);
  glAttachShader(shaderId, fragment);
  glLinkProgram(shaderId);
  glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
    std::cout << "Error shader link fail\n" << infoLog << std::endl;
  }
  std::cout << "shader program created " << shaderId << "\n";

  glValidateProgram(shaderId);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}


void Shaders::Shader::use() {
  glUseProgram(shaderId);
  glBindVertexArray(vaoId);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Shaders::Shader::getId() {
  return shaderId;
}

void Shaders::Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int) value);
}

void Shaders::Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}


void Shaders::Shader::setFloat(const std::string &name, float value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shaders::Shader::printInfo() {
  std::cout << "shaderId: " << shaderId << "\n";
  std::cout << "vertexContent:\n" << vertexContent << "\n";
  std::cout << "fragmentContent:\n" << fragmentContent << "\n";
  std::cout << "vertexSize: " << vertexSize << "\n";
  for (int i = 0; i < vertexSize; i++) {
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "vaoId: " << vaoId << "\n";
}
