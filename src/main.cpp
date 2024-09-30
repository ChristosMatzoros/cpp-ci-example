// main.cpp
#include <iostream>
#include <vector>
#include "sequential_cholesky.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Example usage of the sequential Cholesky solver
    std::vector<std::vector<double>> A = {
        {4, 12, -16},
        {12, 37, -43},
        {-16, -43, 98}
    };

    std::vector<std::vector<double>> L;
    if (sequential_cholesky::decompose(A, L)) {
        std::cout << "Cholesky decomposition successful." << std::endl;
    } else {
        std::cout << "Cholesky decomposition failed." << std::endl;
    }

    return 0;
}