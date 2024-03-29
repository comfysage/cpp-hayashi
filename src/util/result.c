#include "util/result.h"

std::string STD_RESULT = "";
std::string ERR_DIR_EXISTS = "dir exists.";
std::string ERR_CONFIG_EXISTS = "config exists.";
std::string ERR_CONFIG_NO_EXISTS = "config doesn't exist.";
std::string ERR_MISSING_COMMAND = "no command specified.";
std::string ERR_MISSING_OBJECT = "no object specified.";
std::string ERR_MISSING_COMMAND_AFTER_ORIGIN = 
  "unqualified command after pkg.";
std::string ERR_INVALID_COMMAND = "unqualified command.";
std::string ERR_PKG_NOT_INSTALLED = "pkg is not installed.";

void result::toss_process() {
  // throw std::runtime_error(v);
  printf({ "" });
  exit(1);
}

result::ResultInfo result::Info(std::string v) {
  return result::ResultInfo(v);
}

result::ResultAwait result::Await() {
  return result::ResultAwait(STD_RESULT);
}
result::ResultAwait result::Await(std::string v) {
  return result::ResultAwait(v);
}

result::ResultOk result::Ok() {
  return result::ResultOk();
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

result::ResultInfo result::printf(std::initializer_list<std::string> s) {
  std::vector<std::string> s_v = s;
  std::string v = "";
  for (int i = 0; i < (int) s_v.size(); i++) {
    v += s_v[i];
  }
  return result::ResultInfo(v);
}

