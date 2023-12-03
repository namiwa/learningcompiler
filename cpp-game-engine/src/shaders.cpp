#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>

#include "shaders/shaders.hpp"
#include "file/file.hpp"

using namespace ghc;

std::string Shaders::setCharsFromFile(std::string& path, const char* contents) {
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath)) return "";
  if (File::pathIsDir(filepath)) return "";
  return File::getFileAsString(filepath.string());
}

Shaders::Shader::Shader(std::string vertexRoot, std::string fragmentRoot, float verticesData[], unsigned int vertexLen) {
  std::string vcontent = setCharsFromFile(vertexRoot, vertexContent);
  std::string fcontent = setCharsFromFile(fragmentRoot, fragmentContent);
  vertexContent = vcontent.c_str();
  fragmentContent = fcontent.c_str();
  vertexSize = vertexLen;
  vertices = (float *) std::malloc(vertexLen * sizeof(float));
  std::memcpy(vertices, verticesData, vertexLen);
  compile();
}

Shaders::Shader::~Shader() {
  if (glIsProgram(shaderId)) {
    glDeleteProgram(shaderId);
  }
}

void Shaders::Shader::compile() {
  std::cout << "compling shaders\n";
  GLint vertex, fragment;
  int success;
  char infoLog[512];
  // add vertices to vbo
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

  // compile vertexShader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexContent, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error vertex shader compilation error\n" << infoLog << std::endl;
  }
  std::cout << "vertex shader created " << vertex << "\n";

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentContent, NULL);
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

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glValidateProgram(shaderId);
}


void Shaders::Shader::use() {

  glUseProgram(shaderId);
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
