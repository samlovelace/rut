
#include <fstream>
#include <iostream>

#include "internal/config_impl.hpp"
#include <nlohmann/json.hpp>

namespace rut::config
{
    ValuePtr parsePrimitive(const nlohmann::json& j)
    {
        if (j.is_null())
            return nullptr;

        auto v = std::make_shared<Value>();

        if (j.is_string())
            v->data = j.get<std::string>();
        else if (j.is_boolean())
            v->data = j.get<bool>();
        else if (j.is_number_integer())
            v->data = j.get<int>();     
        else if (j.is_number_unsigned())
            v->data = j.get<uint64_t>();
        else if (j.is_number_float())
            v->data = j.get<double>();
        else
        {
            // TODO: binary, or throw?
            // For now let's just store as string representation
            v->data = j.dump();
        }

        return v;
    }

    ValuePtr convert(const nlohmann::json& j)
    {
        if (j.is_primitive())
            return parsePrimitive(j);

        auto v = std::make_shared<Value>();

        if (j.is_array())
        {
            Array arr;
            arr.reserve(j.size());

            for (const auto& elem : j)
                arr.push_back(convert(elem));

            v->data = std::move(arr);
        }
        else if (j.is_object())
        {
            Object obj;
            obj.reserve(j.size());

            for (const auto& [key, value] : j.items())
                obj.emplace(key, convert(value));

            v->data = std::move(obj);
        }

        return v;
    }

    Config loadJson(const std::string& path)
    {
        using json = nlohmann::json; 
        json j;
        
        try
        {
            std::ifstream file(path);
            if (!file.is_open())
                throw std::runtime_error("Cannot open file: " + path);

            file >> j;
        }
        catch (const json::parse_error& e)
        {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }

        auto impl = std::make_shared<Config::Impl>();

        Object root;
        root.reserve(j.size());

        for (const auto& [key, val] : j.items())
            root.emplace(key, convert(val));

        impl->root.data = std::move(root);

        return Config{impl};
    }

} // namespace rut::config
