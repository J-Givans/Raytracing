target_sources(${CMAKE_PROJECT_NAME}
target_include_directories(raytracer PUBLIC "${PROJECT_SOURCE_DIR}/include")
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

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Microsoft.GSL::GSL
        gtest::gtest
)

target_compile_options(${CMAKE_PROJECT_NAME}
    PUBLIC
        -Wall -Werror -Wextra -Wundef
)

target_compile_features(${CMAKE_PROJECT_NAME}
    PUBLIC
        cxx_std_17
)