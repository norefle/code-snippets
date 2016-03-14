#include <cstdlib>
#include <iostream>

#include "lib/application.hpp"
#include "lib/type_list.hpp"

#include "modules/bind.hpp"
#include "modules/sample.hpp"
#include "modules/units.hpp"
#include "modules/algorithms.hpp"

//==================================================================================================
// Entry point.
//==================================================================================================

int main(int argc, const char** argv)
{
    MAIN_INIT(
        module::UnitsModule,
        module::BinderModule,
        module::AlgorithmsModule,
        module::SampleModule
    );

    lib::Application mainApp(argc, argv);

    return mainApp.execute() ? EXIT_SUCCESS : EXIT_FAILURE;
}
