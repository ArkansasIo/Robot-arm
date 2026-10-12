cmake_minimum_required(VERSION 3.20)
project(ForgeArm VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(forgearm
    src/kinematics.cpp
    src/trajectory.cpp
    src/workspace.cpp
    src/collision.cpp
    src/simulator.cpp
)
target_include_directories(forgearm PUBLIC include)
target_compile_features(forgearm PUBLIC cxx_std_23)

if(MSVC)
    target_compile_options(forgearm PRIVATE /W4 /permissive-)
else()
    target_compile_options(forgearm PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

add_executable(forgearm_demo src/main.cpp)
target_link_libraries(forgearm_demo PRIVATE forgearm)

enable_testing()
foreach(test_name IN ITEMS kinematics trajectory workspace collision)
    add_executable(forgearm_test_${test_name} tests/test_${test_name}.cpp)
    target_link_libraries(forgearm_test_${test_name} PRIVATE forgearm)
    add_test(NAME ${test_name} COMMAND forgearm_test_${test_name})
endforeach()
