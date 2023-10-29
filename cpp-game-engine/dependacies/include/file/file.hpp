#ifndef file_utils_hpp
#define file_utils_hpp

#include <string>
// TODO: bug in filesystem import for experimental vs native
#include "filesystem/filesystem.hpp"

namespace File {
  ghc::filesystem::path cleanPath(std::string path);
  bool pathExists(std::string path);
  bool pathIsDir(std::string path);
  std::string getFileAsString(std::string path);
  bool writeStrToFile(std::string path, std::string contents, bool overwrite);
};

#endif // !file_utils_hpp
