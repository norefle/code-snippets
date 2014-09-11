#pragma once

#include <iostream>
#include <string>

#include "lib/module_list.hpp"

/** Usage: DECLARE_CLASS_NAME(ClassType); */
#define DECLARE_CLASS_NAME(self)                                    \
    static const std::string& toString()                            \
    {                                                               \
        static const std::string name = #self;                      \
        return name;                                                \
    }                                                               \


namespace lib
{

template<class TSelf>
struct IModule
{
public:
    /** Registers module to be executed by application. */
    static void apply();

    /** Executes main modules routine. */
    virtual bool execute(const lib::ArgumentCollection& commandLine) = 0;

    /** Virtual destructor. */
    virtual ~IModule() { }
};

template<class TSelf>
void IModule<TSelf>::apply()
{
    lib::ModuleList::create().add(
        [](const std::string& prefix, const lib::ArgumentCollection& commandLine) -> bool
        {
            std::cout << prefix << TSelf::toString() << ":" << std::endl;
            TSelf instance;
            const bool result = instance.execute(commandLine);
            std::cout << "Done: " << result << std::endl << std::endl;
            return result;
        }
    );
}

}
