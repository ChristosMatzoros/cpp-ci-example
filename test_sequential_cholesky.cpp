// test_sequential_cholesky.cpp
#include "sequential_cholesky.h"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>

// Helper function to compare matrices
bool matricesAreEqual(const std::vector<std::vector<double>>& A,
                      const std::vector<std::vector<double>>& B,
                      double epsilon = 1e-6) {
    if (A.size() != B.size()) return false;
    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i].size() != B[i].size()) return false;
        for (size_t j = 0; j < A[i].size(); ++j) {
            if (std::abs(A[i][j] - B[i][j]) > epsilon) return false;
        }
    }
    return true;
}

TEST(SequentialCholeskyTest, PositiveDefiniteMatrix) {
    // Example symmetric positive-definite matrix
    std::vector<std::vector<double>> A = {
        {25, 15, -5},
        {15, 18,  0},
        {-5,  0, 11}
    };

    std::vector<std::vector<double>> L;

    bool success = sequential_cholesky::decompose(A, L);

    EXPECT_TRUE(success);

    // Reconstruct A from L
    int n = A.size();
    std::vector<std::vector<double>> LLT(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= std::min(i, j); ++k) {
                LLT[i][j] += L[i][k] * L[j][k];
            }
            LLT[j][i] = LLT[i][j]; // Symmetric
        }
    }

    // Compare LLT and A
    EXPECT_TRUE(matricesAreEqual(LLT, A));
}

TEST(SequentialCholeskyTest, NonPositiveDefiniteMatrix) {
    // A symmetric matrix that is not positive-definite
    std::vector<std::vector<double>> A = {
        {1, 2},
        {2, 1}
    };

    std::vector<std::vector<double>> L;

    bool success = sequential_cholesky::decompose(A, L);

    EXPECT_FALSE(success);
}

TEST(SequentialCholeskyTest, IdentityMatrix) {
    // Identity matrix
    std::vector<std::vector<double>> A = {
        {1, 0},
        {0, 1}
    };

    std::vector<std::vector<double>> L;

    bool success = sequential_cholesky::decompose(A, L);

    EXPECT_TRUE(success);

    // L should be identity matrix
    EXPECT_TRUE(matricesAreEqual(L, A));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
