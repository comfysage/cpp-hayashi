#pragma once

#include "util/std.h"
#include "util/config.h"
#include "util/forest.h"

struct Opts {
  bool verbose = false;
  bool force = false;
  bool edit = false;
};

struct State {
  Opts opts;
  Config config;

  std::string cmd;
  std::vector<std::string> argv;

  forest::Forest forest;
};

extern struct State state;
