#include "util/config.h"

Config read_config() {
std::fstream fs(HAYASHI_ROOT + "/.hayashi");
  Config config;
  Serializer<Config>().deserialize(config, fs);
  return config;
}
