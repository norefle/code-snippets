#pragma once

#include <functional>

#include "lib/module.hpp"

namespace module
{

/** Example module. */
class UnitsModule : public lib::IModule<UnitsModule>
{
public:
    DECLARE_CLASS_NAME(UnitsModule);

    /** Executes module and shows its arguments. */
    virtual bool execute(const lib::ArgumentCollection& commandLine);
};

} // namespace module
