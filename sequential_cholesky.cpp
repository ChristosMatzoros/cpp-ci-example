// sequential_cholesky.cpp
#include "sequential_cholesky.h"
#include <cmath>
#include <stdexcept>

namespace sequential_cholesky {

bool decompose(const std::vector<std::vector<double>>& A,
               std::vector<std::vector<double>>& L) {
    int n = A.size();

    // Initialize L as zero matrix
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    // Perform the Cholesky decomposition
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;

            if (j == i) { // Diagonal elements
                for (int k = 0; k < j; k++)
                    sum += L[j][k] * L[j][k];
                double val = A[j][j] - sum;
                if (val <= 0) return false; // Not positive-definite
                L[j][j] = std::sqrt(val);
            } else {
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return true;
}

} // namespace sequential_cholesky
