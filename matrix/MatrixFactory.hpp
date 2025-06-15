//
// Created by hexy on 25-6-15.
//

#ifndef MATRIXFACTORY_HPP
#define MATRIXFACTORY_HPP

#include "MatrixBase.hpp"
#include <vector>
#include <string>

class MatrixFactory {
public:
    // 创建稠密矩阵
    static MatrixBase* createDenseMatrix(size_t rows, size_t cols,
                                         const std::vector<double>& data);

    // 创建 CSR 格式稀疏矩阵
    static MatrixBase* createSparseCSRMatrix(size_t rows, size_t cols,
                                             const std::vector<double>& values,
                                             const std::vector<int>& colIndices,
                                             const std::vector<int>& rowPtr);

    // 创建 CSC 格式稀疏矩阵
    static MatrixBase* createSparseCSCMatrix(size_t rows, size_t cols,
                                             const std::vector<double>& values,
                                             const std::vector<int>& rowIndices,
                                             const std::vector<int>& colPtr);

    // 自动判断矩阵是否稀疏，并创建合适的矩阵类型
    static MatrixBase* createMatrixFromDenseData(size_t rows, size_t cols,
                                                 const std::vector<double>& data,
                                                 double sparseThreshold = 0.1);
};

#endif // MATRIXFACTORY_HPP
