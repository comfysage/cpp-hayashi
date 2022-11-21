#pragma once

#include "util/result.h"
#include "util/path.h"
#include "util/constants.h"

#include "util/exec.h"
#include "pkg/pkg.h"

/* # removes custom pkg
 * - checks for existence of pkg config
 * - removes pkg config file
 */
result::Result pkg_remove(Pkg pkg);
