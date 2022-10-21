#pragma once

#include "util/std.h"
#include "data/file.h"
#include "util/constants.h"
#include "serialization/serializer.h"
#include "util/ini.h"

struct Config {
  bool shallow_clone;
};

template <>
struct Serializer<Config> {
  void serialize(const Config &t, std::ostream &out) const {
    ini::Object object;
    object.insert("config");
    object.sections[object.currentsection]
      .insert(ini::tuple_v{"shallow-clone", t.shallow_clone ? "true" : "false"});
    Serializer<ini::Object>().serialize(object, out);
  }
  void deserialize(Config &t, std::istream &in) const {
    ini::Object object;
    Serializer<ini::Object>().deserialize(object, in);
    std::string s_val = std::get<1>(
        std::get<1>(
          std::get<1>(
            object.at("config") ).at("shallow-clone") ));
    t.shallow_clone = s_val == "true";
  }
};

/* read file root + .hayashi
 * parse to struct
 * returns Config
 */
Config read_config();
