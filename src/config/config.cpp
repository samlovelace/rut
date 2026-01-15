// src/config/config.cpp

#include <iostream> 

#include <rut/config/config.hpp>
#include "internal/config_impl.hpp"
#include "internal/config_loaders.hpp"

namespace rut::config {

Config::Config(std::shared_ptr<const Impl> impl) 
    : mImpl(std::move(impl))
{

}

Config Config::fromFile(const std::string& path) 
{
    // decide which backend to use
    if(path.find(".yaml") != std::string::npos)
    {
        std::cout << "Loading yaml configuration file\n"; 
        return loadYaml(path); 
    }
    else if (path.find(".json") != std::string::npos)
    {
        std::cout << "Loading JSON configuration file\n"; 
        return loadJson(path); 
    }
    else 
    {
        throw std::runtime_error("Unsupported config type"); 
    }
}

bool Config::has(const std::string& key) const 
{
    return mImpl->find(key) != nullptr;
}

template<typename T>
T Config::get(const std::string& key) const 
{
    const auto* value = mImpl->find(key);
    if (!value)
        throw std::runtime_error("Missing key: " + key);
    return std::get<T>(*value);
}

} // namespace rut::config
