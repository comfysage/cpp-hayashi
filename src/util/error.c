#include "error.h"

int error_no_cmd() {
  throw std::runtime_error("no command specified.");
  return 1;
}
int error_no_obj() {
  throw std::runtime_error("no object specified.");
  return 1;
}
int error_dir_exists() {
  throw std::runtime_error("dir already exists");
  return 1;
}
