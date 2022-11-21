#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/constants.h"

#include "util/exec.h"

#include "pkg/pkg.h"
#include "data/management.h"
#include "state.h"

/* # adds config with pkg under custom collection
 * - checks for existence of config
 * - writes config file
 */
result::Result pkg_add(Pkg pkg);
