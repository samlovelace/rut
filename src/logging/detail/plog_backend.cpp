// src/logging/detail/plog_logger.cpp

#include "logging/detail/plog_backend.hpp"
#include "plog/Log.h"
#include "plog/Init.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"

namespace rut::logging::detail{

PlogBackend::PlogBackend()
{

}

PlogBackend::~PlogBackend()
{

}

bool PlogBackend::init(const std::string& filename)
{
    if (mInitialized)
        return true;

    mFileAppender = std::make_unique<plog::RollingFileAppender<plog::CsvFormatter>>(filename.c_str());
    mConsoleAppender = std::make_unique<plog::ColorConsoleAppender<plog::TxtFormatter>>();

    plog::init(plog::verbose, mFileAppender.get())
        .addAppender(mConsoleAppender.get());

    mInitialized = true;
    return true;
}

void PlogBackend::write(const std::string& line, Level level)
{
    if (!mInitialized)
        return;

    switch (level)
    {
    case Level::INFO:    LOGI << line; break;
    case Level::DEBUG:   LOGD << line; break;
    case Level::VERBOSE: LOGV << line; break;
    case Level::WARNING: LOGW << line; break;
    case Level::ERROR:   LOGE << line; break;
    default:             LOGI << line; break;
    }
}

} // namespace rut::logging::detail
