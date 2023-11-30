#include <iostream>

#include "shaders/shaders.hpp"
#include "file/file.hpp"

using namespace ghc;

std::string Shaders::setCharsFromFile(std::string& path, const char* contents) {
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath)) return "";
  if (File::pathIsDir(filepath)) return "";
  return File::getFileAsString(filepath.string());
}

Shaders::Shader::Shader(std::string vertexRoot, std::string fragmentRoot) {
  std::string vcontent = setCharsFromFile(vertexRoot, vertexContent);
  std::string fcontent = setCharsFromFile(fragmentRoot, fragmentContent);
  vertexContent = vcontent.c_str();
  fragmentContent = fcontent.c_str();
  compile();
}

Shaders::Shader::~Shader() {
  if (shaderId != nullptr) {
    glDeleteProgram(*shaderId);
  }
}

void Shaders::Shader::compile() {
  GLint vertex, fragment;
  int success;
  char infoLog[512];

  // compile vertexShader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexContent, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error vertex shader compilation error\n" << infoLog << std::endl;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentContent, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "Error fragment shader compilation error\n" << infoLog << std::endl;
  }

  *shaderId = glCreateProgram();
  glAttachShader(*shaderId, vertex);
  glAttachShader(*shaderId, fragment);
  glLinkProgram(*shaderId);

  glGetProgramiv(*shaderId, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(*shaderId, 512, NULL, infoLog);
    std::cout << "Error shader link fail\n" << infoLog << std::endl;
  }

  glValidateProgram(*shaderId);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}


void Shaders::Shader::use() {
  glUseProgram(*shaderId);
}

GLint* Shaders::Shader::getId() {
  return shaderId;
}

void Shaders::Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(*shaderId, name.c_str()), (int) value);
}

void Shaders::Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(*shaderId, name.c_str()), value);
}


void Shaders::Shader::setFloat(const std::string &name, float value) const {
  glUniform1i(glGetUniformLocation(*shaderId, name.c_str()), value);
}
