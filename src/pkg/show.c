#include "pkg/show.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

result::Result pkg_show(std::string name) {
result::Await("showing pkg config.");

  path::search_pkg(name);

  Pkg pkg;
  pkg = get_pkg(name);

  // name
  result::printf({ ANSI_COLOR_MAGENTA + pkg.name });

  if (pkg.desc != "") {
result::printf({ ANSI_COLOR_RESET + pkg.desc });
  }

  // url
  if (pkg.url != "") {
result::printf({ ANSI_COLOR_CYAN "url  " ANSI_COLOR_RESET + pkg.url });
  }
  if (pkg.bash != "") {
result::printf({ ANSI_COLOR_CYAN "bash " ANSI_COLOR_RESET + pkg.bash });
  }

  result::printf({""});

  return result::Ok();
}
