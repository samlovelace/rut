// src/logging/detail/ilogger_backend.hpp

#pragma once

#include <string>
#include "rut/logging/logging_types.hpp"

namespace rut::logging::detail {

class ILoggerBackend
{
public:
    virtual ~ILoggerBackend() = default;

    virtual bool init(const std::string& fileName) = 0;
    virtual void write(const std::string& line, Level level) = 0;

    //virtual LogId create(const std::string& fileName) = 0;
    //virtual void write(LogId logId, const std::string& line, Level level) = 0;
};

} // namespace rut::logging::detail
