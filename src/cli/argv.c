#include "argv.h"

void parse_option(std::string o) {
  while(o[0] == '-') {
    o = o.erase(0, 1);
  }
  if (o == "verbose") {
    state.opts.verbose = true;
    return;
  }
  if (o == "force") {
    state.opts.force = true;
    return;
  }
  if (o == "edit") {
    state.opts.edit = true;
    return;
  }
}

result::Result parse_arg(std::vector<std::string> args) {
result::Await("parsing arguments.");
  for (int i = 2; i < (int) args.size(); i++) {
    if (args[i][0] == '-') {
      parse_option(args[i]);
    } else {
      state.argv.push_back(args[i]);
    }
  }
  if (args.size() == 1) {
    return result::Err(ERR_MISSING_COMMAND);
  }

  state.cmd = args[1];

  if (state.argv.size() == 0) {
    return result::Err(ERR_MISSING_OBJECT);
  }
  return result::Ok("args saved to state.");
}
