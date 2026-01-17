
#include <iostream>
#include <rut/config/config.hpp>

int main()
{
    std::cout << "Testing YAML configuration file...\n";  
    auto cfg = rut::config::Config::fromFile("../test.yaml");
    int test = cfg.get<int>("Testing.Other");
    std::cout << test << std::endl; 

    std::cout << "####################################" << std::endl; 
    std::cout << "Testing JSON configuration file...\n";
    auto jcfg = rut::config::Config::fromFile("../test.json"); 
    int other = jcfg.get<int>("person.age"); 
    std::cout << other << std::endl; 
}