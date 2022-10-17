#pragma once

#include "util/std.h"
#include "util/config.h"
#include "util/tree.h"

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

  tree::Tree tree;
};

extern struct State state;
