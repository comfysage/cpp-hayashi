#pragma once

#include "util/std.h"
#include "data/file.h"
#include "util/constants.h"
#include "serialization/serializer.h"

struct Config {
  bool shallow_clone;
};

template <>
struct Serializer<Config> {
  void serialize(const Config &t, std::ostream &out) const {
    Serializer<bool>().serialize(t.shallow_clone, out);
  }
  void deserialize(Config &t, std::istream &in) const {
    Serializer<bool>().deserialize(t.shallow_clone, in);
  }
};

/* read file root + .hayashi
 * parse to struct
 * returns Config
 */
Config read_config();
