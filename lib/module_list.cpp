#include "lib/module_list.hpp"

#include <sstream>

namespace lib
{

ModuleList::ModuleList()
{
}

ModuleList& ModuleList::create()
{
    static ModuleList instance;

    return instance;
}

bool ModuleList::add(Module module)
{
    bool added = false;
    if(module)
    {
        modules_.push_back(module);
        added = true;
    }

    return added;
}

bool ModuleList::runAll(const ArgumentCollection& commandLine)
{
    bool success = true;

    std::stringstream prefix;
    const size_t amount = modules_.size();
    size_t current = 1;
    for(auto module : modules_)
    {
        prefix << "[" << current << "|" << amount << "] ";

        const bool currentResult = module(prefix.str(), commandLine);
        success = success && currentResult;

        ++current;
        prefix.str("");
        prefix.clear();
    }

    return success;
}


} // namespace lib
