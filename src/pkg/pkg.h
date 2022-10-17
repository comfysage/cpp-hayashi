#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/constants.h"
#include "serialization/serializer.h"

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
    Serializer<std::string>().serialize(t.name, out);
    Serializer<std::string>().serialize(t.url, out);
    Serializer<std::string>().serialize(t.bash, out);
  }
  void deserialize(Pkg &t, std::istream &in) const {
    Serializer<std::string>().deserialize(t.name, in);
    Serializer<std::string>().deserialize(t.url, in);
    // Serializer<std::string>().deserialize(t.bash, in);
    std::string b;
    while(in) {
      Serializer<std::string>().deserialize(b, in);
      t.bash += b + "\n";
    }
  }
};
