#pragma once

#include "util/result.h"
#include "util/path.h"
#include "util/constants.h"

#include "util/exec.h"
#include "pkg/pkg.h"

result::Result pkg_remove(Pkg pkg);
