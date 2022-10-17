#include "util/constants.h"

std::string HOME = std::getenv("HOME");

std::string HAYASHI_ROOT = HOME + "/.hayashi";

int C_SUCCESS = 0;
int C_FAIL = 1;
int C_IGNORE = 2;

int T_SUCCESS = C_SUCCESS;
int T_FAIL = C_FAIL;
int T_IGNORE = C_IGNORE;
int T_NEW = C_IGNORE + 1;
