#pragma once

#include "lib/module_list.hpp"

/** Application's implementation. */
namespace lib
{

/** Entry point of the program. */
class Application
{
public:
    /** Creates main application and parses its parameters from command line. */
    Application(int amount, const char** arguments);

    /** Executes application. */
    bool execute();

private:
    /** Parsed command line arguments. */
    ArgumentCollection arguments_;
};

} // namespace lib
