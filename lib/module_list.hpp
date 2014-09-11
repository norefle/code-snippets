#pragma once

#include <iostream>
#include <functional>
#include <list>
#include <string>

#include "lib/type_list.hpp"

namespace lib
{

/** Collection of command line arguments. */
typedef std::list<std::string> ArgumentCollection;

/** Injection type. */
typedef std::function<bool(const std::string&, const std::list<std::string>&)> Module;

/** List of all registered modules. */
class ModuleList
{
public:
    /** Creates the only worker list instance. */
    static ModuleList& create();

    /** Adds worker. */
    bool add(Module module);

    /** Executes all workers step by step. */
    bool runAll(const ArgumentCollection& commandLine);

private:
    /** Creates instance, closed due to its singleton nature. */
    ModuleList();

    // It's singleton, any copy methods are forbidden.
    ModuleList(const ModuleList&) = delete;
    ModuleList& operator = (const ModuleList&) = delete;

private:
    /** Collection of registered modules. */
    typedef std::list<Module> ModuleCollection;

    /** Workers. */
    ModuleCollection modules_;

};

} // namespace lib

/** To unify modules registration use MAIN_INIT(ModuleClass, ModuleClass, ModuleClass). */
#define MAIN_INIT(...) lib::apply<lib::TypeList, __VA_ARGS__, std::nullptr_t>()
