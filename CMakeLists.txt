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
find_package(OpenGL REQUIRED)

include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS} imgui ${OPENGL_INCLUDE_DIRS} glm)


source_group(src REGULAR_EXPRESSION src)
source_group(imgui REGULAR_EXPRESSION imgui)

add_executable(AnyNEAT ${SOURCES})

target_link_libraries(AnyNEAT ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )

