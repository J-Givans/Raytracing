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

find_package(Microsoft.GSL REQUIRED)
find_package(GTest REQUIRED gtest_main gmock_main)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)