#pragma once

#include "util/std.h"
#include "util/forest.h"
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
    forest::Node n(v, c);
    state.forest.add(n);
  }
};

struct ResultInfo : Result {
  const std::string &v;
  int &c = T_INFO;

  ResultInfo(const std::string &v) : v(v) {
    this->capture();
  }
  void toss() { }
  void capture() {
    // printf("\n -- %s --", this->v.c_str());
    forest::Node n(v, c);
    state.forest.add(n);
  }

};
ResultInfo Info(std::string v);

struct ResultAwait : Result {
  const std::string &v;
  int &c = T_NEW;
  forest::Node n;

  ResultAwait(const std::string &v) : v(v), n(v, c) {
    this->capture();
  }
  void toss() { }
  void capture() {
    // printf("\n -- %s --", this->v.c_str());
    state.forest.add(n);
  }

};
ResultAwait Await();
ResultAwait Await(std::string v);

struct ResultOk : Result {
  const std::string &v;
  int &c = C_SUCCESS;

  ResultOk() : v(state.forest.n[state.forest.n.size() - 1].v) {
    this->toss();
  }
  ResultOk(const std::string &v) : v(v) {
    this->capture();
  }
  void toss() {
    state.forest.toss();
  }
  void capture() {
    // printf("\n -- %s --", this->v.c_str());
    forest::Node n(v, c);
    state.forest.add(n);
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
    forest::Node n(v, c);
    state.forest.add(n);
  }
};
ResultErr Err(std::string &v);
ResultErr Err(std::string &v, int &c);

ResultInfo printf(std::initializer_list<std::string> s);

}

