target_sources(${CMAKE_PROJECT_NAME}
target_include_directories(raytracer PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(raytracer
    PUBLIC
        main.cpp
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/Common.hpp"
        Vec3.cpp
        "${PROJECT_SOURCE_DIR}/include/Colour.hpp"
        Colour.cpp
        "${PROJECT_SOURCE_DIR}/include/Hittable.hpp"
        "${PROJECT_SOURCE_DIR}/include/HittableList.hpp"
        HittableList.cpp
        "${PROJECT_SOURCE_DIR}/include/Sphere.hpp"
        Sphere.cpp
)

target_compile_options(raytracer
    PRIVATE
        Microsoft.GSL::GSL
        gtest::gtest
)

    PUBLIC
        -Wall -Werror -Wextra -Wundef
)

target_compile_features(raytracer
    PUBLIC
        cxx_std_17
)