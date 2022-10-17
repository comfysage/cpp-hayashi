#include "pkg/add.h"

result::Result pkg_add(std::string name) {
result::Await("adding pkg config.");

  if (path_exists(HAYASHI_ROOT + "/." + name)) result::Err(ERR_CONFIG_EXISTS, state.opts.force ? C_IGNORE : C_FAIL);

  Pkg pkg;
  pkg.name = name;

  save_pkg(pkg);

  return result::Ok("added config.");
}

result::Result pkg_add(std::string name, std::string url) {

  pkg_add(name);

result::Await("adding url for pkg.");

  Pkg pkg = get_pkg(name);

  pkg.url = url;
  save_pkg(pkg);

  return result::Ok("added url.");
}
