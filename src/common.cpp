#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
  std::ifstream fileIn(filename);
  if (!fileIn.is_open()) {
    std::cout << "Fail to open file : " << filename << std::endl;
    return std::nullopt;
  }

  std::stringstream text;
  text << fileIn.rdbuf();
  return text.str();
}