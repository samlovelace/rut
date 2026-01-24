#ifndef LOGGING_TYPES_HPP
#define LOGGING_TYPES_HPP

#include <cstdint>

namespace rut::logging
{
    enum class Backend
    {
        PLOG, 
        SPDLOG, 
    }; 

    using LogId = uint32_t; 

    enum class Level
    {
        INFO, 
        DEBUG, 
        VERBOSE, 
        WARNING, 
        ERROR
    };


} // namespace rut::logging
#endif