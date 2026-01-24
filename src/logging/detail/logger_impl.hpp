// src/logging/detail/logger_impl.hpp

#include <rut/logging/logger.hpp>
#include "logging/detail/plog_backend.hpp"


namespace rut::logging
{
    struct Logger::Impl
    {
        explicit Impl(Backend backend)
        {
            switch (backend)
            {
            case Backend::PLOG:
                mBackend = std::make_unique<detail::PlogBackend>();
                break;

            case Backend::SPDLOG:
                //mBackend = std::make_unique<detail::SpdlogBackend>();
                break;
            }
        }

        std::unique_ptr<detail::ILoggerBackend> mBackend;
        
        std::string mMainLogDir; 
        std::string mMainLogTimestamp;

    };
} // namespace rut::logging
