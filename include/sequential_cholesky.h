// sequential_cholesky.h
#ifndef SEQUENTIAL_CHOLESKY_H
#define SEQUENTIAL_CHOLESKY_H

#include <vector>

namespace sequential_cholesky {

bool decompose(const std::vector<std::vector<double>>& A,
               std::vector<std::vector<double>>& L);

} // namespace sequential_cholesky

#endif // SEQUENTIAL_CHOLESKY_H
