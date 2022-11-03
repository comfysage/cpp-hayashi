#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/constants.h"
#include "util/path.h"

#include "util/exec.h"

#include "pkg/pkg.h"
#include "data/management.h"
#include "state.h"

result::Result clone_pkg(std::string name);

/* # installs pkg by name
 * - reads config
 * - clones git url
 * - runs bash script
 */
result::Result pkg_install(std::string name);
