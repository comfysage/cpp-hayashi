#include "cli/action.h"

result::Result install() {
result::Await("installing pkg.");
  for (size_t i = 0; i < state.argv.size(); i++) {
    pkg_install(state.argv[i]);
  }
  return result::Ok();
}

result::Result uninstall() {
result::Await("uninstalling pkg.");
  return result::Ok();
}

result::Result show() {
result::Await("show pkg.");
  pkg_show(state.argv[0]);
  return result::Ok();
}

result::Result add() {
result::Await("adding pkg.");
  if (state.argv.size() == 1) {
    return result::Err(ERR_MISSING_OBJECT);
  }

  Pkg pkg;
  pkg.name = state.argv[1];
  
  if (state.argv.size() == 3) {
    pkg.url = state.argv[2];
  }

  pkg_add(pkg);

  return result::Ok();
}

result::Result remove() {
result::Await("removing pkg.");
  if (state.argv.size() == 1) {
    return result::Err(ERR_MISSING_OBJECT);
  }
  Pkg pkg;
  pkg.name = state.argv[1];

  pkg_remove(pkg);

  return result::Ok();
}

result::Result update() {
result::Await("updating pkg.");
  for (size_t i = 0; i < state.argv.size(); i++) {
    Pkg pkg = get_pkg(state.argv[i]);
    pkg_update(pkg);
  }
  return result::Ok();
}
