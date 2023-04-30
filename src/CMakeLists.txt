find_package(Microsoft.GSL REQUIRED)

target_link_libraries(raytracer
    PRIVATE
        Microsoft.GSL::GSL
)

target_include_directories(raytracer PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(raytracer
    PUBLIC
        main.cpp

        "${PROJECT_SOURCE_DIR}/include/Common.hpp"
        "${PROJECT_SOURCE_DIR}/include/Colour.hpp"
        "${PROJECT_SOURCE_DIR}/include/Hittable.hpp"
        "${PROJECT_SOURCE_DIR}/include/HittableList.hpp"
        "${PROJECT_SOURCE_DIR}/include/Sphere.hpp"
    PRIVATE
        Vec3.cpp
        Colour.cpp
        HittableList.cpp
        Sphere.cpp
)

target_compile_options(raytracer
    PUBLIC
        -Wall -Werror -Wextra -Wundef
)

target_compile_features(raytracer
    PUBLIC
        cxx_std_17
)