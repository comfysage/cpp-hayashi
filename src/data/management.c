#include "data/management.h"

bool path_exists(std::string name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}
