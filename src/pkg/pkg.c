#include "pkg/pkg.h"

result::Result save_pkg(struct Pkg pkg) {
result::Await("saving pkg config.");
std::string path = HAYASHI_ROOT + "/." + pkg.name;
std::fstream fs;
  fs.open(path, std::fstream::out | std::fstream::trunc);
  if (!fs) {
  result::Await("creating new config.");
    fs << "";
  result::Ok("config created.");
  }
  Serializer<Pkg>().serialize(pkg, fs);
  return result::Ok("config saved.");
}

Pkg get_pkg(std::string name) {
std::fstream fs(HAYASHI_ROOT + "/." + name);
  Pkg pkg;
  Serializer<Pkg>().deserialize(pkg, fs);
  return pkg;
}
