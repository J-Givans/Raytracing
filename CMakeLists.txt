cmake_minimum_required(VERSION 3.20)

project(raytracing
    VERSION 0.0.1
    DESCRIPTION "A raytracer"
    LANGUAGES CXX
)

find_program(CCACHE ccache)

if (CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE}")
endif()

add_executable(raytracer)

add_subdirectory(src)
add_subdirectory(tests)