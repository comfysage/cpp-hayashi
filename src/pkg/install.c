#include "pkg/install.h"

result::Result clone_pkg(Pkg &pkg) {
result::Await("cloning pkg.");
  if (path_exists(path::repo(pkg.name))) 
    result::Err(ERR_DIR_EXISTS, state.opts.force ? C_IGNORE : C_FAIL);

  result::printf({ "url: ", pkg.url });

  if (state.config.shallow_clone) {
    runin(REPO_ROOT, "git clone --depth 1 " + pkg.url + " -o " + pkg.name);
  } else {
    runin(REPO_ROOT, "git clone " + pkg.url + " -o " + pkg.name);
  }
  return result::Ok();
}

result::Result pkg_install(std::string name) {
result::Await("install pkg.");

  Pkg pkg = get_pkg(name);

  clone_pkg(pkg);

result::Await("building pkg.");
  runin(path::repo(pkg.name), pkg.bash);
result::Ok();

  return result::Ok();
}
