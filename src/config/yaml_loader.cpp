
#include <iostream>

#include <rut/config/config.hpp>
#include "internal/config_impl.hpp"

namespace rut::config
{
    Config loadYaml(const std::string& aPath)
    {   
        auto impl = std::make_shared<Config::Impl>(); 
        impl->message = "YAML"; 

        Config cfg(impl);
        std::cout << "Returning YAML impl\n";  
        return cfg; 
    }
} // namespace rut::config
