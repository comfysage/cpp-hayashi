#include "util/std.h"
#include "util/result.h"
#include "cli/argv.h"
#include "cli/action.h"

#include "state.h"

result::Result validate_cmd() {
// result::Await("running command.");

  if (state.cmd == "show") {
    return show();
  }
  if (state.cmd == "add") {
    return install();
  }
  if (state.cmd == "remove") {
    return uninstall();
  }
  if (state.cmd == "update") {
    return update();
  }
  if (state.cmd == "pkg") {
    if (state.argv[0] == "add") {
      return add();
    }
    if (state.argv[0] == "remove") {
      return remove();
    }
    return result::Err(ERR_MISSING_COMMAND_AFTER_ORIGIN);
  }
  return result::Err(ERR_INVALID_COMMAND);
}

int main(int argc, char *argv[]) {

// result::Await("main");

std::vector<std::string> args(argv, argv + argc);

  parse_arg(args);

  if (state.opts.verbose) {
    // printf("%s - %s", state.cmd.c_str(), state.argv[0].c_str());
  std::cout <<std::endl;
  }

  state.config = read_config();

  validate_cmd();

  return 0;
}
