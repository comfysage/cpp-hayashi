#include "pkg/update.h"

result::Result fetch_pkg(Pkg &pkg) {
result::Await("fetching pkg.");

  if (!path_exists(path::repo(pkg.name))) {
    return result::Err(ERR_PKG_NOT_INSTALLED, C_FAIL);
  }

std::string s = "";
  s = s + "fetching " + ANSI_COLOR_MAGENTA + pkg.name + ANSI_COLOR_RESET + " from " + ANSI_COLOR_YELLOW + pkg.url + ANSI_COLOR_RESET + " ...";
result::printf({ s });

  runin(path::repo(pkg.name), "git fetch && git merge $( git remote )/$( git branch --show-current )");

    if (pkg.script.update == "") {
    runin(path::repo(pkg.name), pkg.script.install);
    } else {
    runin(path::repo(pkg.name), pkg.script.update);
    }

    return result::Ok();
  }

result::Result pkg_update(Pkg pkg) {
  result::Await("updating pkg.");

    if (path_exists(path::repo(pkg.name))) {
      return fetch_pkg(pkg);
    }

    return result::Err(ERR_PKG_NOT_INSTALLED, C_FAIL);
  }
