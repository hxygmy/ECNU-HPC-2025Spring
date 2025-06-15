//
// Created by hexy on 25-6-15.
//
#include "MatrixFactory.hpp"

#include <stdexcept>

#include "DenseMatrix.hpp"
#include "SparseMatrixCSR.hpp"
#include "SparseMatrixCSC.hpp"

MatrixBase* MatrixFactory::createDenseMatrix(size_t rows, size_t cols,
                                             const std::vector<double>& data) {
    return new DenseMatrix(rows, cols, data);
}

MatrixBase* MatrixFactory::createSparseCSRMatrix(size_t rows, size_t cols,
                                                 const std::vector<double>& values,
                                                 const std::vector<int>& colIndices,
                                                 const std::vector<int>& rowPtr) {
    return new SparseMatrixCSR(rows, cols, values, colIndices, rowPtr);
}

MatrixBase* MatrixFactory::createSparseCSCMatrix(size_t rows, size_t cols,
                                                 const std::vector<double>& values,
                                                 const std::vector<int>& rowIndices,
                                                 const std::vector<int>& colPtr) {
    return new SparseMatrixCSC(rows, cols, values, rowIndices, colPtr);
}

MatrixBase* MatrixFactory::createMatrixFromDenseData(size_t rows, size_t cols,
                                                     const std::vector<double>& data,
                                                     double sparseThreshold) {
    size_t total = rows * cols;
    if (total != data.size()) {
        throw std::invalid_argument("输入数据集参数非法");
    }

    size_t nonZeros = 0;
    for (double val : data) {
        if (val != 0.0) ++nonZeros;
    }

    double density = static_cast<double>(nonZeros) / total;
    if (density < sparseThreshold) {
        // 转换为 CSR 格式
        std::vector<double> values;
        std::vector<int> colIndices;
        std::vector<int> rowPtr(rows + 1, 0);

        int nnz = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                double val = data[i * cols + j];
                if (val != 0.0) {
                    values.push_back(val);
                    colIndices.push_back(static_cast<int>(j));
                    ++nnz;
                }
            }
            rowPtr[i + 1] = nnz;
        }

        return new SparseMatrixCSR(rows, cols, values, colIndices, rowPtr);
    } else {
        return new DenseMatrix(rows, cols, data);
    }
}