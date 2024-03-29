#pragma once

#include "util/std.h"
#include "util/result.h"
#include "util/path.h"
#include "serialization/serializer.h"
#include "util/datastruct.h"
#include "util/ini.h"

struct Pkg {
  std::string name = "";
  std::string desc = "";
  std::string url = "";
  struct Script {
  std::string install = "";
  std::string remove = "";
  std::string update = "";
  } script;
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
    IniTuple<std::string>().serialize("name", t.name, object);
    IniTuple<std::string>().serialize("description", t.desc, object);
    IniTuple<std::string>().serialize("url", t.url, object);
    object.insert("script");
    IniTuple<std::string>().serialize("install", t.script.install, object);
    IniTuple<std::string>().serialize("remove", t.script.remove, object);
    IniTuple<std::string>().serialize("update", t.script.update, object);
    Serializer<ini::Object>().serialize(object, out);
  }
  void deserialize(Pkg &t, std::istream &in) const {
    ini::Object object;
    Serializer<ini::Object>().deserialize(object, in);
    IniTuple<std::string>().deserialize("pkg", "name", t.name, object);
    IniTuple<std::string>().deserialize("pkg", "description", t.desc, object);
    IniTuple<std::string>().deserialize("pkg", "url", t.url, object);
    IniTuple<std::string>().deserialize("script", "install", t.script.install, object);
    IniTuple<std::string>().deserialize("script", "remove", t.script.remove, object);
    IniTuple<std::string>().deserialize("script", "update", t.script.update, object);
  }
};
