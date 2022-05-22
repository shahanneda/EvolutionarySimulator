cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

project(AnyNEAT)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
    imgui/*.h
    imgui/*.cpp
)


find_package(SDL2 REQUIRED)
include_directories(AnyNEAT ${SDL2_INCLUDE_DIRS} imgui)

add_executable(AnyNEAT ${SOURCES})
target_link_libraries(AnyNEAT ${SDL2_LIBRARIES})

