#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/constants.h"
#include "util/path.h"

#include "util/exec.h"

#include "pkg/pkg.h"
#include "data/management.h"
#include "state.h"

/* # clones pkg
 * - checks for existence of cloned repo
 * - clones pkg from url
 * */
result::Result clone_pkg(Pkg &pkg);

/* # installs pkg by name
 * - reads pkg
 * - clones git url
 * - runs install script
 */
result::Result pkg_install(std::string name);
