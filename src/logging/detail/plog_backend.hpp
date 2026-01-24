
#pragma once 

#include <memory>

#include "logging/detail/ilogger_backend.hpp"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"

namespace rut::logging::detail
{

class PlogBackend : public ILoggerBackend
{
public:
    PlogBackend();
    ~PlogBackend() override;

    bool init(const std::string& filename) override;
    void write(const std::string& line, Level level) override;

private:
    bool mInitialized{false};

    std::unique_ptr<
        plog::RollingFileAppender<plog::CsvFormatter>
    > mFileAppender;

    std::unique_ptr<
        plog::ColorConsoleAppender<plog::TxtFormatter>
    > mConsoleAppender;
};

} // namespace rut::logging
