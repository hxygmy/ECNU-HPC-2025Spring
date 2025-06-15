//
// Created by hexy on 25-6-14.
//
#include "DenseMatrix.hpp"
#include <iostream>
#include <iomanip>

// 构造函数
DenseMatrix::DenseMatrix(size_t rows, size_t cols)
    : numRows(rows), numCols(cols), data(rows * cols, 0.0) {}

DenseMatrix::DenseMatrix(size_t rows, size_t cols, const std::vector<double>& values)
    : numRows(rows), numCols(cols), data(values) {
    if (rows * cols != values.size()) {
        throw std::invalid_argument("构造参数传入不正确");
    }
}

// 拷贝构造函数
DenseMatrix::DenseMatrix(const DenseMatrix& other)
    : numRows(other.numRows), numCols(other.numCols), data(other.data) {}

DenseMatrix& DenseMatrix::operator=(const DenseMatrix& other) {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        data = other.data;
    }
    return *this;
}

// 非零元素的数量除以所有元素数量
double DenseMatrix::density() const {
    size_t nonZeros = 0;
    for (double val : data) {
        if (val != 0.0) ++nonZeros;
    }
    return static_cast<double>(nonZeros) / data.size();
}

// 数据访问
double DenseMatrix::get(size_t i, size_t j) const {
    if (i >= numRows || j >= numCols) {
        throw std::out_of_range("数组越界");
    }
    return data[i * numCols + j];
}

void DenseMatrix::set(size_t i, size_t j, double value) {
    if (i >= numRows || j >= numCols) {
        throw std::out_of_range("数组越界");
    }
    data[i * numCols + j] = value;
}

// Doubao assist
void DenseMatrix::print(int maxRows, int maxCols) const {
    std::cout << "DenseMatrix (" << numRows << "x" << numCols << "):\n";
    int printRows = std::min(static_cast<int>(numRows), maxRows);
    int printCols = std::min(static_cast<int>(numCols), maxCols);

    for (int i = 0; i < printRows; ++i) {
        for (int j = 0; j < printCols; ++j) {
            std::cout << std::setw(8) << get(i, j);
        }
        if (printCols < static_cast<int>(numCols)) std::cout << " ...";
        std::cout << "\n";
    }
    if (printRows < static_cast<int>(numRows)) std::cout << " ...\n";
}