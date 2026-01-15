// rut/config/config.hpp

#pragma once
#include <string>
#include <optional>
#include <memory>

namespace rut::config {

class Config {

    // forward declare the impl 
public: struct Impl;

public:
    static Config fromFile(const std::string& path);

    bool has(const std::string& key) const;

    template<typename T>
    T get(const std::string& key) const;

    template<typename T>
    std::optional<T> getOptional(const std::string& key) const;

private:
    std::shared_ptr<const Impl> mImpl;

    explicit Config(std::shared_ptr<const Impl> impl);

    friend Config loadYaml(const std::string&);
    friend Config loadJson(const std::string&);

};

} // namespace rut::config
