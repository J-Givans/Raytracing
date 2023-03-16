target_sources(${CMAKE_PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/main.cpp
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/Common/Common.hpp
        ${PROJECT_SOURCE_DIR}/src/Common/Common.cpp
        
        ${PROJECT_SOURCE_DIR}/src/Vec3/Vec3.cpp
        
        ${PROJECT_SOURCE_DIR}/include/Colour/Colour.hpp
        ${PROJECT_SOURCE_DIR}/src/Colour/Colour.cpp
        
        ${PROJECT_SOURCE_DIR}/include/Hittable/Hittable.hpp
        ${PROJECT_SOURCE_DIR}/src/Hittable/Hittable.cpp
        
        ${PROJECT_SOURCE_DIR}/include/HittableList/HittableList.hpp
        ${PROJECT_SOURCE_DIR}/src/HittableList/HittableList.cpp
        
        ${PROJECT_SOURCE_DIR}/include/Sphere/Sphere.hpp
        ${PROJECT_SOURCE_DIR}/src/Sphere/Sphere.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

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