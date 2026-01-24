// src/logging/logging.cpp

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <filesystem>  // Cross-platform file system library
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>


#include <rut/logging/logger.hpp>
#include "detail/logger_impl.hpp"

namespace rut::logging
{
    Logger::Logger(Backend aBackend) : mImpl(std::make_unique<Impl>(aBackend))
    {}

    Logger::~Logger()
    {}

    static bool directoryExists(const std::string& directoryName) 
    {
        return std::filesystem::exists(directoryName) && std::filesystem::is_directory(directoryName);
    }

    void static createDirectory(const std::string& directoryName) 
    {
        if (!directoryExists(directoryName)) 
        {
            std::filesystem::create_directories(directoryName);  // Create directories recursively if needed
        }
    }

    bool Logger::init(const std::string& filename)
    {
        // get current YYYY_MM_DD
        // Get current date and time
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()) % 60;

        struct passwd *pw = getpwuid(getuid());
        if (pw == nullptr) 
        {
            std::cerr << "Failed to get username.\n";
            return false;
        }
        std::string username = pw->pw_name;

        // Directory path
        std::string dirPath = "/home/" + username + "/testing/";

        // Format date in YYYY_MM_DD
        std::ostringstream dateSS;
        dateSS << dirPath + "/test_" << std::put_time(std::localtime(&now_time_t), "%Y_%m_%d");
        mImpl->mMainLogDir = dateSS.str();

        // Create directory if it doesn't already exist
        createDirectory(mImpl->mMainLogDir);

        // Format time in HH_MM_SS
        std::ostringstream timeSS;
        timeSS << std::put_time(std::localtime(&now_time_t), "%H_%M_") << std::setw(2) << std::setfill('0') << seconds.count();
        mImpl->mMainLogTimestamp = timeSS.str();

        // full log file name 
        std::string logFileName = mImpl->mMainLogDir + "/" + filename + mImpl->mMainLogTimestamp + ".csv"; 
        mImpl->mBackend->init(filename); 

        return true; 
    }

    void Logger::write(const std::string& line, Level level)
    {
        mImpl->mBackend->write(line, level); 
    }

} // namespace rut::logging
