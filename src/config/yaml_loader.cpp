
#include <iostream>

#include <rut/config/config.hpp>
#include "detail/config_impl.hpp"

#include <yaml-cpp/yaml.h>

namespace rut::config
{

    ValuePtr parseScalarNode(const YAML::Node& aScalarNode)
    {
        auto v = std::make_shared<Value>(); 
        const std::string s = aScalarNode.Scalar();

        // Try int
        try {
            v->data = aScalarNode.as<int>();
            return v;
        } catch (...) {}

        // Try double
        try {
            v->data = aScalarNode.as<double>();
            return v;
        } catch (...) {}

        // Try bool
        try {
            v->data = aScalarNode.as<bool>();
            return v;
        } catch (...) {}

        // Fallback: store as string
        v->data = s;
        return v; 
    }

    ValuePtr convert(const YAML::Node& aNode)
    {
        if(!aNode || aNode.IsNull())
        {
            // TODO: should i do this instead of having a null type 
            return nullptr; 
        }

        auto v = std::make_shared<Value>(); 

        if (aNode.IsScalar()) 
        {
            return parseScalarNode(aNode);  
        }

        if(aNode.IsSequence())
        {
            Array arr; 

            for(const auto& elem : aNode)
            {
                arr.push_back(convert(elem)); 
            }
            
            v->data = std::move(arr); 
            return v; 
        }

        if(aNode.IsMap())
        {
            Object obj; 

            for(const auto& kv : aNode)
            {
                std::string key = kv.first.as<std::string>(); 
                obj[key] = convert(kv.second); 
            }

            v->data = std::move(obj); 
            return v; 
        }

        return v;
    }

    Config loadYaml(const std::string& aPath)
    {   
        auto impl = std::make_shared<Config::Impl>();

        // load yaml file 
        YAML::Node node = YAML::LoadFile(aPath);
        Object root; 

        for(const auto& kv : node)
        {
            std::string key = kv.first.as<std::string>();  
            root.insert({key, convert(kv.second)}); 
        }

        // assign to impl 
        impl->root.data = root; 
        Config cfg(impl);  
        return cfg; 
    }

} // namespace rut::config
