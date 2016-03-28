#include "modules/algorithms.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "algorithms/stack_queue.hpp"

namespace module {

bool AlgorithmsModule::execute(const lib::ArgumentCollection& /*commandLine*/) {
    auto tasks = {
        std::make_tuple("Stack", std::bind(&solveStackAsQueues)),
        std::make_tuple("Queue", std::bind(&solveQueueAsStacks))
    };

    for (auto& task: tasks) {
        std::cout << std::get<0>(task) << ": " << std::get<1>(task)() << std::endl;
    }

    return true;
}

} // module
