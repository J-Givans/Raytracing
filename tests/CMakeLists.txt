add_executable(tests)

find_package(GTest REQUIRED COMPONENTS gtest_main gmock_main)

target_link_libraries(tests 
    PRIVATE
        GTest::gtest_main 
        GTest::gmock_main
)

target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(tests
    PUBLIC
        Vec3.test.cpp
        Camera.test.cpp
        Ray.test.cpp
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/Vec3.hpp"
        "${PROJECT_SOURCE_DIR}/include/Camera.hpp"
        "${PROJECT_SOURCE_DIR}/include/Ray.hpp"
)

target_compile_features(tests PRIVATE cxx_std_17)

target_compile_options(tests PRIVATE -Wall -Wextra -Werror)