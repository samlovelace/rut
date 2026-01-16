
#include <iostream>

#include "internal/config_impl.hpp"

namespace rut::config
{
    Config loadJson(const std::string& aPath)
    {
        auto impl = std::make_shared<Config::Impl>();  
        
        Config cfg(impl); 
        return cfg; 
    }
} // namespace rut::config
