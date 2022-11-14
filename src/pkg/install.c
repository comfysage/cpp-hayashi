#include "pkg/install.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

result::Result clone_pkg(Pkg &pkg) {
result::Await("cloning pkg.");
  if (path_exists(path::repo(pkg.name))) {
    result::Err(ERR_DIR_EXISTS, state.opts.force ? C_IGNORE : C_FAIL);
    runin(REPO_ROOT, "rm '" + pkg.name + "' -rf");
  }

  std::string s = "";
  s = s + "cloning " + ANSI_COLOR_MAGENTA + pkg.name + ANSI_COLOR_RESET + " from " + ANSI_COLOR_YELLOW + pkg.url + ANSI_COLOR_RESET + " ...";
  result::printf({ s });

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
  std::string s = "";
  s = s + "building " + ANSI_COLOR_MAGENTA + pkg.name + ANSI_COLOR_RESET + " at " + ANSI_COLOR_BLUE + path::repo(pkg.name) + ANSI_COLOR_RESET + " ...";
  result::printf({ s });
  s = "";
  s = s + ANSI_COLOR_GREEN + pkg.script.install;
  result::printf({ s });
  runin(path::repo(pkg.name), pkg.script.install);
result::Ok();

  return result::Ok();
}
