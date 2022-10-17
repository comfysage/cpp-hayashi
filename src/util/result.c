#include "util/result.h"

std::string STD_RESULT = "";
std::string ERR_DIR_EXISTS = "dir exists.";
std::string ERR_CONFIG_EXISTS = "config exists.";
std::string ERR_MISSING_COMMAND = "no command specified.";
std::string ERR_MISSING_OBJECT = "no object specified.";
std::string ERR_MISSING_COMMAND_AFTER_ORIGIN = 
  "unqualified command after pkg.";
std::string ERR_INVALID_COMMAND = "unqualified command.";

void result::toss_process() {
  // throw std::runtime_error(v);
  printf("\n\n");
  exit(1);
}

result::ResultAwait result::Await() {
  return result::ResultAwait(STD_RESULT);
}
result::ResultAwait result::Await(std::string v) {
  return result::ResultAwait(v);
}

result::ResultOk result::Ok() {
  return result::ResultOk(STD_RESULT);
}
result::ResultOk result::Ok(std::string v) {
  return result::ResultOk(v);
}

result::ResultErr result::Err(std::string &v) {
result::ResultErr err(v);
  return err;
}
result::ResultErr result::Err(std::string &v, int &c) {
result::ResultErr err(v, c);
  return err;
}
