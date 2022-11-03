#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/path.h"
#include "serialization/serializer.h"
#include "util/ini.h"

struct Pkg {
  std::string name = "";
  std::string url = "";
  std::string bash = "";
};

/* struct -> json|ini|yaml
 * save string to file:
 *   root + name
 */
result::Result save_pkg(struct Pkg pkg);

/* search for file based on root + name
 * parse file -> json|ini|yaml
 * returns pkg
 */
Pkg get_pkg(std::string name);

template <>
struct Serializer<Pkg> {
  void serialize(const Pkg &t, std::ostream &out) const {
    ini::Object object;
    object.insert("pkg");
    object.sections[object.currentsection]
      .insert(ini::tuple_v{"name", t.name});
    object.sections[object.currentsection]
      .insert(ini::tuple_v{"url", t.url});
    object.sections[object.currentsection]
      .insert(ini::tuple_v{"bash", t.bash});
    Serializer<ini::Object>().serialize(object, out);
  }
  void deserialize(Pkg &t, std::istream &in) const {
    ini::Object object;
    Serializer<ini::Object>().deserialize(object, in);
    t.name = object.get("pkg", "name");
    t.url = object.get("pkg", "url");
    t.bash = object.get("pkg", "bash");
  }
};
