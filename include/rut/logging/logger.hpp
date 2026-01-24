#ifndef LOGGER_HPP
#define LOGGER_HPP
 
#include <string>
#include <memory> 

#include "rut/logging/logging_types.hpp"

namespace rut::logging{
 
class Logger 
{ 
    struct Impl; 

public:
    Logger(Backend aBackend);
    ~Logger();

    bool init(const std::string& aFileName); 
    void write(const std::string& aLine, Level aLevel); 

    //LogId create(const std::string& aFileName); 
    //void write(LogId aLogId, const std::string& aLine, Level aLevel);

private:
    std::unique_ptr<Impl> mImpl;
};

}
#endif //LOGGER_HPP