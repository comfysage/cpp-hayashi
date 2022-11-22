#pragma once

#include <string>
#include "util/result.h"
#include "util/path.h"
#include "util/exec.h"
#include "util/constants.h"

#include "pkg/pkg.h"
#include "pkg/install.h"
#include "data/management.h"

/* # fetch update and run update
 * - checks if repo is cloned
 *   otherwise runs pkg_install
 * - runs git fetch and merge
 * - runs update ( or install ) command
 */
result::Result fetch_pkg(Pkg &pkg);

/* # update pkg
 * - checks if repo is cloned
 *   otherwise runs pkg_install
 * */
result::Result pkg_update(Pkg pkg);
