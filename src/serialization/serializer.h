#pragma once

#include "util/num.h"
#include "util/std.h"

template <typename T>
struct Serializer {
  virtual void serialize(const T &t, std::ostream &out) const {}
  virtual void deserialize(T &t, std::istream &in) const {}
};

// Serializers

// std::string
template <>
struct Serializer<std::string> {
  void serialize(const std::string &t, std::ostream &out) const {
    // printf("\n >:< %s >:<\n", t.c_str());
    out << t + "\n";
  }
  void deserialize(std::string &t, std::istream &in) const {
    // printf("\n <:> %s <:>\n", t.c_str());
    std::getline(in, t);
  }
};

// bool
template <>
struct Serializer<bool> {
  void serialize(const bool &t, std::ostream &out) const {
    if (t) {
     out << "true";
    } else {
     out << "false";
    }
  }
  void deserialize(bool &t, std::istream &in) const {
    std::string s;
    std::getline(in, s);
    if (s == "true") {
     t = true;
    }
    if (s == "false") {
     t = false;
    }
  }
};

// defines a serializer for primitive type _t
#define _PRIMITIVE_SERIALIZER(_t, _f)                            \
  template <>                                                    \
  struct Serializer<_t> {                                        \
    void serialize(const _t &data, std::ostream &out) const {    \
      out << _f;                                                 \
    }                                                            \
                                                                 \
    void deserialize(_t &data, std::istream &in) const {         \
      in >> _f;                                                  \
    }                                                            \
  };

_PRIMITIVE_SERIALIZER(u8, data)
_PRIMITIVE_SERIALIZER(u16, data)
/* _PRIMITIVE_SERIALIZER(u32)
_PRIMITIVE_SERIALIZER(u64)

_PRIMITIVE_SERIALIZER(i8)
_PRIMITIVE_SERIALIZER(i16)
_PRIMITIVE_SERIALIZER(i32)
_PRIMITIVE_SERIALIZER(i64)

_PRIMITIVE_SERIALIZER(f32)
_PRIMITIVE_SERIALIZER(f64)

_PRIMITIVE_SERIALIZER(bool) */
