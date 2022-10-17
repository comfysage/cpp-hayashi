#include "file.h"

std::string read_file(std::string path) {
std::ifstream t(path);
std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

int write_file(std::string path, std::string data) {
std::ofstream o(path);
  o << data;
  o.close();
  return 0;
}
