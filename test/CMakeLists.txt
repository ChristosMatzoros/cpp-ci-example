# test/CMakeLists.txt

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add Google Test
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest googletest)

# Find Threads package (required for linking pthread)
find_package(Threads REQUIRED)

# Add test executable
add_executable(test_sequential_cholesky test_sequential_cholesky.cpp)

# Link test executable against the library and Google Test libraries
target_link_libraries(test_sequential_cholesky
    PRIVATE
        sequential_cholesky_lib
        gtest
        gtest_main
        Threads::Threads
)

# Include directories for the test target
target_include_directories(test_sequential_cholesky
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Add test to CTest
add_test(NAME SequentialCholeskyTest COMMAND test_sequential_cholesky)
