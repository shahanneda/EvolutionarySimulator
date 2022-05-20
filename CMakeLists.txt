cmake_minimum_required(VERSION 3.10)

# set the project name
project(AnyNEAT)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)


# SDL2
find_package(SDL2 REQUIRED)
include_directories(AnyNEAT ${SDL2_INCLUDE_DIRS})

add_executable(AnyNEAT ${SOURCES})
target_link_libraries(AnyNEAT ${SDL2_LIBRARIES})

