#include "util/path.h"

std::string path::cl(std::string cl) {
  return PKG_ROOT + "/" + cl;
}

std::string path::name(std::string name) {
  return name + ".ini";
}

std::string path::pkg_cl(std::string cl, std::string name) {
  return path::cl(cl) + "/" + path::name(name);
}

bool path::pkg_exists(std::string cl, std::string name) {
  return path_exists(path::pkg_cl(cl, name));
}

std::string path::search_pkg(std::string name) {
  if (path::pkg_exists("core", name)) return pkg_cl("core", name);

  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(PKG_ROOT.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL) {
      if (path::pkg_exists(ent->d_name, name)) return pkg_cl(ent->d_name, name);
    }
    closedir(dir);
  }

result::Err(ERR_CONFIG_NO_EXISTS, C_FAIL);
  return "";
}

std::string path::repo(std::string name) {
  return REPO_ROOT + "/" + name;
}
