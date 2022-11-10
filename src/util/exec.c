#include "exec.h"

int run(std::string code) {
  // std::array<char, 128> buffer;
std::string line = code + "> /dev/null 2>&1";
std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(line.c_str(), "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
    return 1;
  }
  return 0;
}

int runin(std::string d, std::string code) {
  return run("cd " + d + "\n" + code);
}

std::string exec(const char* cmd) {
std::array<char, 128> buffer;
std::string result;
std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}
