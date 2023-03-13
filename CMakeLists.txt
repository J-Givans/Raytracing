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

add_executable("${CMAKE_PROJECT_NAME}")

target_sources("${CMAKE_PROJECT_NAME}"
    PUBLIC
        main.cpp
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Common.hpp
        ${PROJECT_SOURCE_DIR}/Colour.hpp
        ${PROJECT_SOURCE_DIR}/Colour.cpp
        ${PROJECT_SOURCE_DIR}/Hittable.hpp
        ${PROJECT_SOURCE_DIR}/HittableList.hpp
        ${PROJECT_SOURCE_DIR}/HittableList.cpp
        ${PROJECT_SOURCE_DIR}/Sphere.hpp
        ${PROJECT_SOURCE_DIR}/Sphere.cpp
)

target_link_libraries("${CMAKE_PROJECT_NAME}" 
    PRIVATE
        Microsoft.GSL::GSL
        gtest::gtest
)

target_compile_options("${CMAKE_PROJECT_NAME}"
    PUBLIC
        -Wall -Werror -Wextra -Wundef
)

target_compile_features("${CMAKE_PROJECT_NAME}"
    PUBLIC
        cxx_std_17
)