#pragma once

#include <functional>

#include "lib/module.hpp"

namespace module
{

/** Example module. */
class BinderModule : public lib::IModule<BinderModule>
{
public:
    DECLARE_CLASS_NAME(BinderModule);

    /** Executes module and shows its arguments. */
    virtual bool execute(const lib::ArgumentCollection& commandLine);
};

} // namespace module
