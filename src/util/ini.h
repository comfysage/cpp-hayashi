#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include "serialization/serializer.h"

namespace ini {

namespace detail {

// trim functions based on http://stackoverflow.com/a/217605

template <class CharT>
inline void ltrim(std::basic_string<CharT> & s, const std::locale & loc) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       [&loc](CharT ch) { return !std::isspace(ch, loc); }));
}

template <class CharT>
inline void rtrim(std::basic_string<CharT> & s, const std::locale & loc) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [&loc](CharT ch) { return !std::isspace(ch, loc);
                       }).base(),
          s.end());
}

template <class CharT, class UnaryPredicate>
inline void rtrim2(std::basic_string<CharT>& s, UnaryPredicate pred) {
  s.erase(std::find_if(s.begin(), s.end(), pred), s.end());
}

// string replacement function based on http://stackoverflow.com/a/3418285

template <class CharT>
inline bool replace(std::basic_string<CharT> & str, const
                    std::basic_string<CharT> & from, const
                    std::basic_string<CharT> & to) {
  auto changed = false;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) !=
    std::basic_string<CharT>::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
      changed = true;
    }
  return changed;
}

} // namespace detail

struct Format {
  // used for generating
  const char char_section_start;
  const char char_section_end;
  const char char_assign;
  const char char_comment;

  // used for parsing
  bool is_section_start(char ch) const { return ch == char_section_start; }
  bool is_section_end(char ch) const { return ch == char_section_end; }
  bool is_assign(char ch) const { return ch == char_assign; }
  bool is_comment(char ch) const { return ch == char_comment; }

  // used for interpolation
  const char char_interpol;
  const char char_interpol_start;
  const char char_interpol_sep;
  const char char_interpol_end;

  Format(char section_start, char section_end, char assign, char comment, char
         interpol, char interpol_start, char interpol_sep, char interpol_end)
    : char_section_start(section_start)
    , char_section_end(section_end)
    , char_assign(assign)
    , char_comment(comment)
    , char_interpol(interpol)
    , char_interpol_start(interpol_start)
    , char_interpol_sep(interpol_sep)
    , char_interpol_end(interpol_end) { }

  Format() : Format('[', ']', '=', ';', '$', '{', ':', '}') { }

  const std::basic_string<char> local_symbol(
    const std::basic_string<char>& name) const {
    return char_interpol + (char_interpol_start + name + char_interpol_end);
  }

  const std::basic_string<char> global_symbol(
    const std::basic_string<char>& sec_name,
    const std::basic_string<char>& name)
  const {
    return local_symbol(sec_name + char_interpol_sep + name);
  }
};

typedef std::tuple<std::string, std::string> tuple_v;

/* # get variable name from tuple_v
 */
inline std::string v_name(tuple_v &v) {
  return std::get<0>(v);
}

/* # get variable value from tuple_v
 */
inline std::string v_value(tuple_v &v) {
  return std::get<1>(v);
}

struct Section {
  std::string name;

  std::vector<tuple_v> var;

  Section(std::string name) : name(name) { }
  Section() : Section("default") { }

  bool has(std::string key) {
    for (int i = 0; i < (int) var.size(); i++) {
      if (v_name(var[i]) == key)
        return true;
    }
    return false;
  }

  std::tuple<bool, tuple_v> at(std::string key) {
    for (int i = 0; i < (int) var.size(); i++) {
      if (v_name(var[i]) == key)
        return std::make_tuple(true, var[i]);
    }
    return std::make_tuple(false, tuple_v{"",""});
  }

  /* if variable doesnt exist, add variable
   * else exit
   */
  void insert(tuple_v v) {
    if (has(v_name(v))) return;
    var.push_back(v);
  }

  /* if variable exists, override variable
   * else add the variable
   */
  void override(tuple_v v) {
    for (int i = 0; i < (int) var.size(); i++) {
      if (v_name(var[i]) == v_name(v)) {
        v_value(var[i]) = v_value(v);
        return;
      }
    }
    this->insert(v);
  }

};

struct Object {

  std::vector<Section> sections = { Section() };
  Section &defaultsection = sections.front();
  int currentsection = 0;

  Object() { }

  bool has(std::string key) {
    for (int i = 0; i < (int) sections.size(); i++) {
      if (sections[i].name == key)
        return true;
    }
    return false;
  }

  std::tuple<bool, Section> at(std::string key) {
    for (int i = 0; i < (int) sections.size(); i++) {
      if (sections[i].name == key)
        return std::make_tuple(true, sections[i]);
    }
    return std::make_tuple(false, defaultsection);
  }

  /* if section exists, exit
   * else push_back section and set to currentsection
   */
  void insert(std::string name) {
    if (has(name)) return;
    sections.push_back(Section(name));
    currentsection = sections.size() - 1;
  }

  /* if section exists, set to currentsection
   * else push_back section and set to currentsection
   */
  void override(std::string name) {
    for (int i = 0; i < (int) sections.size(); i++) {
      if (sections[i].name == name) {
        currentsection = i;
        return;
      }
    }
    this->insert(name);
  }

  std::string get(std::string section, std::string key) {
    Section s = std::get<1>(this->at(section));
    tuple_v v = std::get<1>(s.at(key));
    return v_value(v);
  }
};

struct Ini {

  Format format;
  std::vector<std::string> errors;

  Object object;

  Ini() { }

  void parse(std::istream &in) {

    std::string line;
    const std::locale loc{"C"};
    while (std::getline(in, line)) {
      detail::ltrim(line, loc);
      detail::rtrim(line, loc);
      const auto length = line.length();
      if (length == 0) 
        errors.push_back(line);

      const auto pos = std::find_if(
          line.begin(), line.end(), [this](char ch) {
            return format.is_assign(ch); });
      /* auto pos = line.end();
      for (auto iter = line.begin(); iter < line.end(); iter++) {
        if (format->is_assign(*iter)) {
          pos = iter;
          break;
        }
      } */
      const auto &front = line.front();

      if (format.is_comment(front)) {
        continue;
      }
      if (format.is_section_start(front)) {
        if (format.is_section_end(line.back()))
          object.override(line.substr(1, length - 2));
        else
          errors.push_back(line);
        continue;
      }
      if (pos != line.begin() && pos != line.end()) {
        std::string variable(line.begin(), pos);
        std::string value(pos + 1, line.end());
        detail::rtrim(variable, loc);
        detail::ltrim(value, loc);
        auto &sec = object.sections[object.currentsection];
        sec.override(tuple_v{variable, value});
      }

    } // while loop

  } // parse function

};

} // namespace ini

template <>
struct Serializer<ini::tuple_v> {
  void serialize(const ini::tuple_v &t, std::ostream &out) const {
    std::string t_name = std::get<0>(t);
    std::string t_value = std::get<1>(t);
    std::string name = t_name == "" ? "null" : t_name;
    std::string value = t_value == "" ? "null" : t_value;
    std::string v = name + "=" + value;
    Serializer<std::string>().serialize(v, out);
  }
  void deserialize(ini::tuple_v &t, std::istream &in) const { }
};

template <>
struct Serializer<std::vector<ini::tuple_v>> {
  void serialize(const std::vector<ini::tuple_v> &t, std::ostream &out) const {
    for (int i = 0; i < (int) t.size(); i++) {
      Serializer<ini::tuple_v>().serialize(t[i], out);
    }
  }
  void deserialize(std::vector<ini::tuple_v> &t, std::istream &in) const { }
};

template <>
struct Serializer<ini::Section> {
  void serialize(const ini::Section &t, std::ostream &out) const {
    std::string v = "[" + t.name + "]";
    Serializer<std::string>().serialize(v, out);
    Serializer<std::vector<ini::tuple_v>>().serialize(t.var, out);
  }
  void deserialize(ini::Section &t, std::istream &in) const { }
};

template <>
struct Serializer<std::vector<ini::Section>> {
  void serialize(const std::vector<ini::Section> &t, std::ostream &out) const {
    for (int i = 0; i < (int) t.size(); i++) {
      if (t[i].var.size() == 0) continue;
      Serializer<ini::Section>().serialize(t[i], out);
    }
  }
  void deserialize(std::vector<ini::Section> &t, std::istream &in) const { }
};

template <>
struct Serializer<ini::Object> {
  void serialize(const ini::Object &t, std::ostream &out) const {
    Serializer<std::vector<ini::Section>>().serialize(t.sections, out);
  }
  void deserialize(ini::Object &t, std::istream &in) const {
    ini::Ini ini;
    ini.parse(in);
    t.sections = ini.object.sections;
  }
};
