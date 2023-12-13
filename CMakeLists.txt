cmake_minimum_required(VERSION 3.12)

project(
        labwork5
        VERSION 1.0
        DESCRIPTION "I LOVE C++"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)


include_directories(.)


add_subdirectory(lib)
add_subdirectory(bin)



enable_testing()
add_subdirectory(tests)
