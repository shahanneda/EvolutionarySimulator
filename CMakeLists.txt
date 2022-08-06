cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-missing-braces")

project(AnyNEAT)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        imgui/*.h
        imgui/*.cpp
        src/network/*.cpp
        src/network/*.h
        )

if (${EMSCRIPTEN})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -s USE_SDL=2 -std=c++1z -pthread -s SAFE_HEAP=1 -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 -g -s PTHREAD_POOL_SIZE=2 -s ALLOW_MEMORY_GROWTH")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/index.html
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else ()
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
endif ()

include_directories(${SDL2_INCLUDE_DIRS} imgui ${OPENGL_INCLUDE_DIRS} glm ./src/network src)


source_group(src REGULAR_EXPRESSION src)
source_group(imgui REGULAR_EXPRESSION imgui)

add_executable(AnyNEAT ${SOURCES})

target_link_libraries(AnyNEAT ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

