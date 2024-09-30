# src/CMakeLists.txt

# Create a library from the sequential Cholesky source
add_library(sequential_cholesky_lib sequential_cholesky.cpp)

# Include directories for the library
target_include_directories(sequential_cholesky_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Add executable for the main program
add_executable(cpp_ci_example main.cpp)

# Link the main executable with the library
target_link_libraries(cpp_ci_example PRIVATE sequential_cholesky_lib)