#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/constants.h"

#include "util/exec.h"

#include "pkg/pkg.h"
#include "data/management.h"
#include "state.h"

/* # adds config for pkg by name
 * - writes config
 * - (optionaly) adds bash
 */
result::Result pkg_add(Pkg pkg);
