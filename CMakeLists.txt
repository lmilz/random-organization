cmake_minimum_required(VERSION 3.16)
project(random_organization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(simulation_lib src/Vec.cpp src/Shape.cpp src/Simulation.cpp)

target_include_directories(simulation_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(Simulation src/main.cpp)

target_link_libraries(Simulation PUBLIC simulation_lib)

# google test
find_package(GTest REQUIRED)

enable_testing()

# Test executable: Simulation tests
add_executable(simulation_test test/test_Vec.cpp test/test_Shape.cpp)

target_link_libraries(simulation_test PRIVATE simulation_lib GTest::GTest GTest::Main)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(simulation_test)
