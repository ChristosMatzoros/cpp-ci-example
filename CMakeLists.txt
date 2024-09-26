# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(cpp_ci_example)

set(CMAKE_CXX_STANDARD 11)

# Add main executable
add_executable(cpp_ci_example main.cpp sequential_cholesky.cpp)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Add test executable
add_executable(test_sequential_cholesky test_sequential_cholesky.cpp sequential_cholesky.cpp)

# Link test executable against Google Test libraries
target_link_libraries(test_sequential_cholesky ${GTEST_LIBRARIES})

# Add test to CTest
add_test(NAME SequentialCholeskyTest COMMAND test_sequential_cholesky)