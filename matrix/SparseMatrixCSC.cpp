//
// Created by hexy on 25-6-14.
//
#include "SparseMatrixCSC.hpp"
#include <iostream>
#include <iomanip>

SparseMatrixCSC::SparseMatrixCSC(size_t rows, size_t cols,
                                 const std::vector<double>& vals,
                                 const std::vector<int>& rowIdx,
                                 const std::vector<int>& colP)
    : numRows(rows), numCols(cols), values(vals), rowIndices(rowIdx), colPtr(colP) {

    if (colPtr.size() != numCols + 1) {
        throw std::invalid_argument("CSC格式输入错误");
    }
    if (!rowIndices.empty() && values.size() != rowIndices.size()) {
        throw std::invalid_argument("CSC格式输入错误");
    }
}

SparseMatrixCSC::SparseMatrixCSC(const SparseMatrixCSC& other)
    : numRows(other.numRows), numCols(other.numCols),
      values(other.values), rowIndices(other.rowIndices), colPtr(other.colPtr) {}

double SparseMatrixCSC::density() const {
    size_t totalElements = numRows * numCols;
    if (totalElements == 0) return 0.0;
    return static_cast<double>(values.size()) / totalElements;
}

// Doubao Assist
void SparseMatrixCSC::print(int maxCols) const {
    std::cout << "SparseMatrixCSC (" << numRows << "x" << numCols << "):\n";
    int printCols = std::min(static_cast<int>(numCols), maxCols);

    for (int j = 0; j < printCols; ++j) {
        int start = colPtr[j];
        int end = colPtr[j + 1];

        std::cout << "Column " << j << ": ";
        for (int k = start; k < end; ++k) {
            std::cout << "(" << rowIndices[k] << ", " << values[k] << ") ";
        }
        std::cout << "\n";
    }

    if (printCols < static_cast<int>(numCols)) {
        std::cout << "...\n";
    }
}