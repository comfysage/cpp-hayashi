#pragma once

#include <string>
#include "util/result.h"
#include "util/path.h"
#include "util/exec.h"
#include "util/constants.h"

#include "pkg/pkg.h"
#include "pkg/install.h"
#include "data/management.h"

result::Result fetch_pkg(Pkg &pkg);

result::Result pkg_update(Pkg pkg);
