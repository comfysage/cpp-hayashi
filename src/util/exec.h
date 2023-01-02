#pragma once

#include "util/std.h"
#include "state.h"

int run(std::string code);

int runin(std::string d, std::string code);

std::string exec(const char* cmd);
