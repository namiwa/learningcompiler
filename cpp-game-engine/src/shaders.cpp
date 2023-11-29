#include "shaders/shaders.hpp"
#include "file/file.hpp"

using namespace ghc;

void Shaders::setCharsFromFile(std::string path, const char* contents) {
  filesystem::path filepath = File::cleanPath(path);
  if (!File::pathExists(filepath)) return;
  if (File::pathIsDir(filepath)) return;
  contents = File::getFileAsString(filepath.string()).c_str();
}

Shaders::Shader::Shader(std::string vertexRoot, std::string fragmentRoot) {
  setCharsFromFile(vertexRoot, vertexContent);
  setCharsFromFile(fragmentRoot, fragmentContent);
}
