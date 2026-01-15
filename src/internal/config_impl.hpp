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
    std::string message; 
    Value root;
    const Value* find(const std::string& path) const
    {
        
    }
};

} // namespace rut::config
