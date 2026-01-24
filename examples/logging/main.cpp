
#include <iostream>
#include <rut/logging/logger.hpp>

int main()
{
    rut::logging::Logger lgr(rut::logging::Backend::PLOG); 
    if(!lgr.init("test_log"))
    {
        std::cerr << "Failed to create log :(\n"; 
        return 1; 
    } 

    lgr.write("Hello log", rut::logging::Level::INFO); 
    lgr.write("This is a warning!", rut::logging::Level::WARNING); 
    lgr.write("THIS IS AN ERROR!!", rut::logging::Level::ERROR); 

    return 0; 
}