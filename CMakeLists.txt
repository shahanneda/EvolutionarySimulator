cmake_minimum_required(VERSION 3.10)

# set the project name
project(AnyNEAT)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)
# add the executable
add_executable(NEAT ${SOURCES})
