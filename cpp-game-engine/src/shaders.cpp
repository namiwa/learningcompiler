#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>

#include "file/file.hpp"
#include "shaders/shaders.hpp"
#include "utils/utils.hpp"

using namespace ghc;

std::string Shaders::setCharsFromFile(std::string &path) {
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath))
    return "";
  if (File::pathIsDir(filepath))
    return "";
  return File::getFileAsString(filepath.string());
}

Shaders::Shader::Shader(std::string vertexRoot, std::string fragmentRoot,
                        float verticesData[], unsigned int vertexLen) {
  vertexContent = setCharsFromFile(vertexRoot);
  fragmentContent = setCharsFromFile(fragmentRoot);
  vertexSize = vertexLen;
  vertices = (float *)std::malloc(vertexLen * sizeof(float));
  std::cout << "size of vertices: " << vertexSize << "\n";
  for (unsigned int i = 0; i < vertexLen; i++) {
    vertices[i] = verticesData[i];
    std::cout << vertices[i] << std::endl;
  }
  compile();
}

Shaders::Shader::~Shader() {
  if (glIsProgram(shaderId)) {
    glDeleteProgram(shaderId);
  }
  free(vertices);
}

void Shaders::Shader::compile() {
  std::cout << "compling shaders\n";
  GLint vertex, fragment;
  int success = 0;
  char infoLog[512];


  // compile vertexShader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  std::cout << "compiling vertexContent: " << vertexContent << std::endl;
  const char *vt = vertexContent.c_str();
  std::cout << vt << " testing vertex content\n";
  glShaderSource(vertex, 1, &vt, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "Error vertex shader compilation error\n"
              << infoLog << std::endl;
    glDeleteShader(vertex);
    return;
  }
  std::cout << "vertex shader created " << vertex << "\n";
	printGlError();

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  std::cout << "compiling fragmentContent: " << fragmentContent << std::endl;
  const char *ft = fragmentContent.c_str();
  std::cout << ft << " testing fragment content\n";
  glShaderSource(fragment, 1, &ft, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "Error fragment shader compilation error\n"
              << infoLog << std::endl;
    glDeleteShader(fragment);
    return;
  }
  std::cout << "fragment shader created " << fragment << "\n";
	printGlError();

  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertex);
  glAttachShader(shaderId, fragment);
  glLinkProgram(shaderId);
  glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
    std::cout << "Error shader link fail\n" << infoLog << std::endl;
    glDetachShader(shaderId, vertex);
    glDetachShader(shaderId, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteProgram(shaderId);
    return;
  }
  std::cout << "shader program created " << shaderId << "\n";

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  glGenVertexArrays(1, &vaoId);
  glGenBuffers(1, &vboId);
  glBindVertexArray(vaoId);

  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	glValidateProgram(shaderId);
	printGlError();
}

void Shaders::Shader::use() {
  std::cout << "using shaders\n";
  glUseProgram(shaderId);
	glBindVertexArray(vaoId);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Shaders::Shader::getId() { return shaderId; }

void Shaders::Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
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
  for (unsigned int i = 0; i < vertexSize; i++) {
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "vaoId: " << vaoId << "\n";
  std::cout << "vboId: " << vboId << "\n";
}
