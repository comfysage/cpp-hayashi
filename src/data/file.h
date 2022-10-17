#pragma once

#include "../util/std.h"

/* read file from pathname
 * returns string
 */
std::string read_file(std::string path);

/* write to file from pathname with data
 * returns 0|1
 */
int write_file(std::string path, std::string data);
