//
// Created by hexy on 25-6-14.
//
#ifndef DENSEMATRIX_HPP
#define DENSEMATRIX_HPP

#include "MatrixBase.hpp"
#include <vector>

class DenseMatrix : public MatrixBase {
private:
    size_t numRows, numCols;
    std::vector<double> data; // DenseMatrix应该按行存储

public:
    // 构造函数
    DenseMatrix(size_t rows, size_t cols);
    DenseMatrix(size_t rows, size_t cols, const std::vector<double>& values);

    // 拷贝构造
    DenseMatrix(const DenseMatrix& other);
    DenseMatrix& operator=(const DenseMatrix& other);

    ~DenseMatrix() override = default;

    // 接口实现
    bool isSparse() const override { return false; }
    size_t rows() const override { return numRows; }
    size_t cols() const override { return numCols; }
    double density() const override;
    std::string type() const override { return "DenseMatrix"; }
    MatrixBase* clone() const override { return new DenseMatrix(*this); }

    // 数据访问
    double get(size_t i, size_t j) const;
    void set(size_t i, size_t j, double value);

    // 直接访问数据指针（用于性能优化）
    const std::vector<double>& getData() const { return data; }
    std::vector<double>& getData() { return data; }

    // 打印矩阵（调试用）
    void print(int maxRows = 5, int maxCols = 5) const;
};

#endif // DENSEMATRIX_HPP