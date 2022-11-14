#pragma once

#include "util/ini.h"

template <typename T>
struct IniTuple {
  virtual void serialize(std::string n, const T &v, ini::Object &o) const {}
  virtual void deserialize(std::string s, std::string n, T &v, ini::Object &o) const {}
};

template <>
struct IniTuple<std::string> {
  void serialize(std::string n, const std::string &v, ini::Object &o) const {
    o.sections[o.currentsection]
     .insert(ini::tuple_v{n, v});
  }
  void deserialize(std::string s, std::string n, std::string &v, ini::Object &o) const {
    v = o.get(s, n);
  }
};

template <>
struct IniTuple<bool> {
  void serialize(std::string n, const bool &v, ini::Object &o) const {
    std::string str = v ? "true" : "false";
    IniTuple<std::string>().serialize(n, str, o);
  }
  void deserialize(std::string s, std::string n, bool &v, ini::Object &o) const {
    std::string str;
    IniTuple<std::string>().deserialize(s, n, str, o);
    v = str == "true";
  }
};

/*  
 *  ser Struct s Out out
 *    obj o;
 *    tuple<string>().ser("str", s.str, o)
 *    tuple<u8>().ser("int", s.int, o)
 *    Serializer<obj>().ser(o, out)
 *
 *  deser Struct s In in
 *    obj o;
 *    Serializer<obj>().deser(o, in)
 *    tuple<string>().deser("default", "str", s.str, o)
 *    tuple<u8>().deser("default", "int", s.int, o)
 *
 */
