#pragma once

#include "util/std.h"
#include "util/constants.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

namespace tree {

struct Node {
  std::string v;
  const int t;

  Node(std::string v, int t) : v(v), t(t) { }

  std::string capture() {

    std::string s = "";

    if (t == T_SUCCESS) {
      s += ANSI_COLOR_GREEN " + ";
    }
    if (t == T_FAIL) {
      s += ANSI_COLOR_RED " - ";
    }
    if (t == T_IGNORE) {
      s += ANSI_COLOR_BLUE " # ";
    }
    if (t == T_NEW) {
      s += ANSI_COLOR_MAGENTA " * ";
    }

    s += v + ANSI_COLOR_RESET;

    return s;
  }
};

struct Tree {

  int i = 0;
  int deltaI = 0;

  Tree() { }

  void add(Node n) {
    printf("\n");
    this->deltaI = 0;

    if (n.t == T_SUCCESS) {
      this->indent(-1);
    } else if (n.t == T_NEW) {
      this->indent(1);
    }

    int l = this->i;
    if (this->deltaI == 1) {
      l--;
    }
    int h = 0;
    while(h < l) {
      printf("|");
      h++;
    }

    if (this->deltaI == 1) {
      printf(ANSI_COLOR_YELLOW "\\");
    } else if (this->deltaI == -1) {
      printf(ANSI_COLOR_GREEN "/");
    }

    printf(ANSI_COLOR_RESET "");

    printf("%s", n.capture().c_str());
  }

  void indent(int n) {
    this->deltaI = n;
    this->i += this->deltaI;
  }
};

}
