target_sources(${CMAKE_PROJECT_NAME}
    PUBLIC
        main.cpp
    PRIVATE
        Common.hpp
        Vec3.cpp
        Colour.hpp
        Colour.cpp
        Hittable.hpp
        HittableList.hpp
        HittableList.cpp
        Sphere.hpp
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