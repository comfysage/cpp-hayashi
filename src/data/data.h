#pragma once

#include "../util/constants.h"
#include "file.h"

/* read file based on root + name
 * returns raw text
 * */
std::string read_pkg(std::string name);

/* save string to file:
 *   root + name
 * returns 0|1
 */
int write_pkg(std::string name, std::string data);
