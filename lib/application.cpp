#include "lib/application.hpp"

#include <string>

#include "lib/module_list.hpp"

namespace lib
{

Application::Application(int amount, const char** arguments)
{
    // Skip first argument, due to its nature (name of executed application).
    for(int index = 1; index < amount; ++index)
    {
        if(arguments[index])
        {
            arguments_.push_back(std::string(arguments[index]));
        }
    }
}

bool Application::execute()
{
    return ModuleList::create().runAll(arguments_);
}

} // namespace lib
