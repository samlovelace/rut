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
    if(path.find(".yaml") != std::string::npos || path.find(".yml") != std::string::npos)
    { 
        return loadYaml(path); 
    }
    else if (path.find(".json") != std::string::npos)
    {
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

const void* Config::getRaw(const std::string& key) const
{
    const Value* v = mImpl->find(key);
    
    if (!v)
        return nullptr;

    return (void*)v;
}

} // namespace rut::config
