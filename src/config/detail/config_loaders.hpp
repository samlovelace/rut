// src/internal/config_loaders.hpp

#pragma once
#include <string>

namespace rut::config {

    Config loadYaml(const std::string& path);
    Config loadJson(const std::string& path);
    Config loadXml(const std::string& path);

}
