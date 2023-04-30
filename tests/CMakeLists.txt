find_package(GTest REQUIRED gtest_main gmock_main)

add_executable(tests)

target_link_libraries(tests 
    PRIVATE 
        GTest::gtest_main 
        GTest::gmock_main
)

target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(tests
    PUBLIC
        Vec3.test.cpp
)