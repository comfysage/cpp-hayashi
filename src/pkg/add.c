#include "pkg/add.h"

result::Result pkg_add(Pkg pkg) {
result::Await("adding pkg config.");

  if (path::pkg_exists("custom", pkg.name))
    result::Err(ERR_CONFIG_EXISTS, state.opts.force ? C_IGNORE : C_FAIL);

  save_pkg(pkg);

  return result::Ok();
}
