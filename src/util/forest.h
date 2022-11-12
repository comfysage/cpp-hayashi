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

namespace forest {

struct Node {
  const std::string v;
  int t;
  int charc = 0;
  std::string chars = "";

  Node(std::string v, int t) : v(v), t(t) {
    this->capture();
  }

  void capture() {
    if (t == T_SUCCESS || t == T_NEW) return;
    std::string s = "";

    if (t == T_FAIL) {
      s += ANSI_COLOR_RED " - ";
    }
    if (t == T_IGNORE) {
      s += ANSI_COLOR_BLUE " # ";
    }

    s += v + ANSI_COLOR_RESET;

    charc = s.size();
    chars = s;
  }
};

struct Forest {

  std::vector<Node> n;

  Forest() { }

  void printfn(std::string c) {
    std::cout << c.c_str();
  }

  /* Add a node to the stack
   * capture its content
   * present the tree
   */
  void add(Node &node) {
    n.push_back(node);

    capture(n.size() - 1);
  }

  /* Go up tree to last await
   * recapture await
   */
  void toss() {
    for (int N = n.size() - 1; N >= 0; N--) {
      if (n[N].t == T_NEW) {
        this->n[N].t = T_SUCCESS;
        capture(N);
        break;
      }
    }
  }

  void capture(int l) {
    printf(ANSI_COLOR_RESET "");

    n[l].capture();
    if (n[l].charc > 0) printf("\n");

    this->printfn(n[l].chars);
  }

};

}
