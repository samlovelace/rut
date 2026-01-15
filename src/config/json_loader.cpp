
#include <iostream>

#include "internal/config_impl.hpp"

namespace rut::config
{
    Config loadJson(const std::string& aPath)
    {
        auto impl = std::make_shared<Config::Impl>(); 
        impl->message = "json"; 
        
        Config cfg(impl);
        std::cout << "Returning JSON impl\n";  
        return cfg; 
    }
} // namespace rut::config
