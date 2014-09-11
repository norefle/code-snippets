#pragma once

#include <functional>

#include "lib/module.hpp"

namespace module
{

/** Example module. */
class SampleModule : public lib::IModule<SampleModule>
{
public:
    DECLARE_CLASS_NAME(SampleModule);

    /** Executes module and shows its arguments. */
    virtual bool execute(const lib::ArgumentCollection& commandLine);
};

} // namespace module
