
#include <iostream>
#include <rut/config/config.hpp>

int main()
{
    auto cfg = rut::config::Config::fromFile("../test.yaml");
    auto otr = rut::config::Config::fromFile("../test.json");  
}