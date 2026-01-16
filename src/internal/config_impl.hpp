// src/internal/config_impl.hpp

#pragma once

#include <rut/config/config.hpp>

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

namespace rut::config {

struct Value;  // forward declaration

using ValuePtr = std::shared_ptr<Value>;
using Array    = std::vector<ValuePtr>;
using Object   = std::unordered_map<std::string, ValuePtr>;

struct Value {
    using Variant = std::variant<
        int,
        double,
        bool,
        std::string,
        Array,
        Object
    >;

    Variant data;
};

struct Config::Impl {
    
    Value root;
    
    const Value* find(const std::string& path) const
    {
        const Value* current = &root; 

        size_t start = 0; 
        while(true)
        {
            size_t dot = path.find('.', start); 
            std::string key = (dot == std::string::npos)
                ? path.substr(start) 
                : path.substr(start, dot - start); 

            if(!std::holds_alternative<Object>(current->data))
                return nullptr; 

            const Object& obj = std::get<Object>(current->data); 

            auto it = obj.find(key); 
            if(it == obj.end())
                return nullptr; 

            current = it->second.get(); 

            if(dot == std::string::npos)
                break; 
            
            start = dot + 1; 
        }

        return current; 
    }
};

} // namespace rut::config
