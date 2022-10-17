#include "data.h"

std::string read_pkg(std::string name) {
  return read_file(HAYASHI_ROOT + "/." + name);
}

int write_pkg(std::string name, std::string data) {
  return write_file(HAYASHI_ROOT + "/." + name, data);
}
