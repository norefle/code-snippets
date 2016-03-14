cmake_minimum_required(VERSION 2.8)
project(code-snipets)

find_package(Boost)

include_directories("${Boost_INCLUDE_DIRS}" "${PROJECT_SOURCE_DIR}")
add_definitions("-std=c++11")

file(GLOB_RECURSE LIBRARY_FILES "lib/*.hpp" "lib/*.cpp")
file(GLOB_RECURSE MODULE_FILES "modules/*.hpp" "modules/*.cpp")

add_executable(code-snipets "main.cpp" ${LIBRARY_FILES} ${MODULE_FILES})
