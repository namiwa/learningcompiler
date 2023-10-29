#include "file/file.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

using namespace ghc;

filesystem::path File::cleanPath(std::string p) {
  return filesystem::path(p);
}

bool File::pathIsDir(std::string p) {
  filesystem::path cp = cleanPath(p);
  return filesystem::is_directory(cp); 
}

bool File::pathExists(std:: string p) {
  filesystem::path cp = cleanPath(p);
  return filesystem::exists(cp);
}

std::string File::getFileAsString(std::string p) {
  std::string line = "";
  if (!File::pathExists(p)) return line;
  filesystem::path cp = cleanPath(p);
  std::vector<std::string> lines;
  std::ifstream input_file(cp.c_str());
  if (!input_file.is_open()) {
    std::cerr << "Could not open file - " << cp << std::endl;
    return line;
  }
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  input_file.close();
  std::string content;
  for (const auto &li : lines) content += li;
  return content;
}

bool File::writeStrToFile(std::string p, std::string contents, bool overwrite) {
  if (!File::pathExists(p)) return false;
  filesystem::path cp = cleanPath(p);
  std::istringstream iss(contents);
  std::ofstream out_file(cp.c_str());
  if (!out_file.is_open()) return false;
  std::string line;
  while (std::getline(iss, line)) {
    out_file << line;
  }
  out_file.close();
  return true;
}

