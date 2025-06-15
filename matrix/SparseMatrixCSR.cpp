//
// Created by hexy on 25-6-14.
//
#include "SparseMatrixCSR.hpp"
#include <iostream>
#include <iomanip>

SparseMatrixCSR::SparseMatrixCSR(size_t rows, size_t cols,
                                 const std::vector<double>& vals,
                                 const std::vector<int>& colsIdx,
                                 const std::vector<int>& rowP)
    : numRows(rows), numCols(cols), values(vals), colIndices(colsIdx), rowPtr(rowP) {

    if (rowPtr.size() != numRows + 1) {
        throw std::invalid_argument("CSR格式输入错误");
    }
    if (!colIndices.empty() && values.size() != colIndices.size()) {
        throw std::invalid_argument("CSR格式输入错误");
    }
}

SparseMatrixCSR::SparseMatrixCSR(const SparseMatrixCSR& other)
    : numRows(other.numRows), numCols(other.numCols),
      values(other.values), colIndices(other.colIndices), rowPtr(other.rowPtr) {}

SparseMatrixCSR& SparseMatrixCSR::operator=(const SparseMatrixCSR& other) {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        values = other.values;
        colIndices = other.colIndices;
        rowPtr = other.rowPtr;
    }
    return *this;
}

double SparseMatrixCSR::density() const {
    size_t totalElements = numRows * numCols;
    if (totalElements == 0) return 0.0;
    return static_cast<double>(values.size()) / totalElements;
}

// Doubao Assist
void SparseMatrixCSR::print(int maxRows) const {
    std::cout << "SparseMatrixCSR (" << numRows << "x" << numCols << "):\n";
    int printRows = std::min(static_cast<int>(numRows), maxRows);

    for (int i = 0; i < printRows; ++i) {
        int start = rowPtr[i];
        int end = rowPtr[i + 1];

        std::cout << "Row " << i << ": ";
        for (int k = start; k < end; ++k) {
            std::cout << "(" << colIndices[k] << ", " << values[k] << ") ";
        }
        std::cout << "\n";
    }

    if (printRows < static_cast<int>(numRows)) {
        std::cout << "...\n";
    }
}