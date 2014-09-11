#include "modules/sample.hpp"

#include <iostream>

namespace module
{

bool SampleModule::execute(const lib::ArgumentCollection& commandLine)
{
    std::cout << "Arguments:" << std::endl;
    for (auto argument : commandLine)
    {
        std::cout << argument << std::endl;
    }

    return true;
}

} // module
