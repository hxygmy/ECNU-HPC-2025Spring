//
// Created by hexy on 25-6-14.
//
#include "../matrix/DenseMatrix.hpp"
#include "../matrix/SparseMatrixCSR.hpp"

int main() {
    std::vector<double> denseData = {1, 2, 3, 4, 5, 6};
    DenseMatrix A(2, 3, denseData);
    A.print();

    std::vector<double> vals = {10, 20, 30};
    std::vector<int> cols = {0, 2, 1};
    std::vector<int> rows = {0, 2, 3};

    SparseMatrixCSR B(2, 3, vals, cols, rows);
    B.print();

    return 0;
}