#pragma once

#include <dirent.h>

#include "util/constants.h"
#include "data/management.h"
#include "util/result.h"

namespace path {

std::string cl(std::string cl);

std::string name(std::string name);

std::string pkg_cl(std::string cl, std::string name);

bool pkg_exists(std::string cl, std::string name);

std::string search_pkg(std::string name);


std::string repo(std::string name);

} // namespace path
