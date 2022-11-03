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
  if (state.argv.size() == 3) {
    pkg_add(state.argv[1], state.argv[2]);
  } else {
    pkg_add(state.argv[1]);
  }

  return result::Ok();
}

result::Result remove() {
result::Await("removing pkg.");
  if (state.argv.size() == 1) {
    return result::Err(ERR_MISSING_OBJECT);
  }

  return result::Ok();
}

result::Result update() {
result::Await("updating pkg.");
  return result::Ok();
}
