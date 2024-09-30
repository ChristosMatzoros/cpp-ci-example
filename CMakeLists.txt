# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(cpp_ci_example)

set(CMAKE_CXX_STANDARD 11)

# Include custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include custom modules
include(AddGitSubmodule)
include(Docs)

# Call the function to check and install Doxygen
find_and_install_doxygen()

# Initialize the googletest submodule
add_git_submodule(external/googletest https://github.com/google/googletest.git)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)