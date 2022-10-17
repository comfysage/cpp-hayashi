#pragma once

#include "state.h"
#include "util/std.h"
#include "util/result.h"

void parse_option(std::string o);

result::Result parse_arg(std::vector<std::string> args);
