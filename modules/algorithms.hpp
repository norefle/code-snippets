#pragma once

#include "lib/module.hpp"

namespace module
{

/** Refreshing knowledge of algorithms. */
class AlgorithmsModule : public lib::IModule<AlgorithmsModule>
{
public:
    DECLARE_CLASS_NAME(AlgorithmsModule);

    bool execute(const lib::ArgumentCollection& commandLine) override;
};

} // namespace module
