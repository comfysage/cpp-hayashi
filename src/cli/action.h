#pragma once

#include "util/std.h"
#include "util/result.h"

#include "pkg/install.h"
#include "pkg/add.h"
#include "pkg/remove.h"
#include "pkg/update.h"
#include "pkg/show.h"

#include "state.h"

/* # install pkg
 * cmd: add
 * obj: **
 */
result::Result install();

/* # uninstall pkg
 * cmd: remove
 * obj: **
 */
result::Result uninstall();

/* # show info about pkg
 * cmd: show
 * obj: *
 */
result::Result show();

/* # add pkg to manager
 * cmd: origin
 * obj: add
 * arg: *
 */
result::Result add();

/* # remove pkg from manager
 * cmd: origin
 * obj: remove
 * arg: *
 */
result::Result remove();

/* # update installed pkg
 * cmd: update
 * obj: *
 */
result::Result update();
