# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(cpp_ci_example)

set(CMAKE_CXX_STANDARD 11)

# Include custom CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(AddGitSubmodule)
include(Docs)

# Call the function to check and install Doxygen
find_and_install_doxygen()

# Initialize the googletest submodule
add_git_submodule(external/googletest https://github.com/google/googletest.git)

# Add main executable
add_executable(cpp_ci_example main.cpp sequential_cholesky.cpp)

# Enable testing
enable_testing()

# Add Google Test
add_subdirectory(external/googletest)

# Include Google Test headers
include_directories(external/googletest/googletest/include)

# Add test executable
add_executable(test_sequential_cholesky test_sequential_cholesky.cpp sequential_cholesky.cpp)

# Link test executable against Google Test libraries
target_link_libraries(test_sequential_cholesky gtest gtest_main pthread)

# Add test to CTest
add_test(NAME SequentialCholeskyTest COMMAND test_sequential_cholesky)
