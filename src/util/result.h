#pragma once

#include "util/std.h"
#include "util/tree.h"
#include "util/constants.h"

#include "state.h"

extern std::string STD_RESULT;
extern std::string ERR_DIR_EXISTS;
extern std::string ERR_CONFIG_EXISTS;
extern std::string ERR_MISSING_COMMAND;
extern std::string ERR_MISSING_OBJECT;
extern std::string ERR_MISSING_COMMAND_AFTER_ORIGIN;
extern std::string ERR_INVALID_COMMAND;
extern std::string ERR_DIR_EXISTS;

namespace result {

void toss_process();

struct Result {
  const std::string &v;
  int &c = C_SUCCESS;

  Result() : v(STD_RESULT) {}
  Result(const std::string &v) : v(v) {
    this->capture();
  }
  virtual void toss() { }
  virtual void capture() {
    // printf("\n __ %s __", this->v.c_str());
    tree::Node n(v, c);
    state.tree.add(n);
  }
};

struct ResultAwait : Result {
  const std::string &v;
  int &c = T_NEW;

  ResultAwait(const std::string &v) : v(v) {
    this->capture();
  }
  void toss() { }
  void capture() {
    // printf("\n -- %s --", this->v.c_str());
    tree::Node n(v, c);
    state.tree.add(n);
  }

};
ResultAwait Await();
ResultAwait Await(std::string v);

struct ResultOk : Result {
  const std::string &v;
  int &c = C_SUCCESS;

  ResultOk(const std::string &v) : v(v) {
    this->capture();
  }
  void toss() { }
  void capture() {
    // printf("\n -- %s --", this->v.c_str());
    tree::Node n(v, c);
    state.tree.add(n);
  }
};
ResultOk Ok();
ResultOk Ok(std::string v);

struct ResultErr : Result {
  const std::string &v;
  const int &c;

  ResultErr(const std::string &v) : v(v), c(C_FAIL) {
    this->capture();
    this->toss();
  }
  ResultErr(const std::string &v, const int &c) : v(v), c(c) {
    this->capture();
    this->toss();
  }
  void toss() {
    if (c == 1) {
      toss_process();
    }
  }
  void capture() {
    // printf("\n ** %s **", this->v.c_str());
    tree::Node n(v, c);
    state.tree.add(n);
  }
};
ResultErr Err(std::string &v);
ResultErr Err(std::string &v, int &c);

}

