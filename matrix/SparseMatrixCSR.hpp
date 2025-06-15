//
// Created by hexy on 25-6-14.
//

/*
CSR 是一种常用的稀疏矩阵存储方式，它将矩阵的非零元素按行存储，并记录每行中非零元素的位置。CSR格式通过三个数组来存储稀疏矩阵的数据：
vals：存储矩阵中的所有非零元素。
colsIdx：存储每个非零元素对应的列索引。
rowP：指示每行开始非零元素的位置。在这个数组中，元素 rowP[i] 表示第 i 行的第一个非零元素在 vals 数组中的位置。
*/
#ifndef SPARSEMATRIXCSR_HPP
#define SPARSEMATRIXCSR_HPP

#include "MatrixBase.hpp"
#include <vector>

class SparseMatrixCSR : public MatrixBase {
private:
    size_t numRows, numCols;
    std::vector<double> values;
    std::vector<int> colIndices;
    std::vector<int> rowPtr;

public:
    // 构造函数
    SparseMatrixCSR(size_t rows, size_t cols,
                    const std::vector<double>& vals,
                    const std::vector<int>& colsIdx,
                    const std::vector<int>& rowP);

    // 拷贝构造
    SparseMatrixCSR(const SparseMatrixCSR& other);
    SparseMatrixCSR& operator=(const SparseMatrixCSR& other);
    ~SparseMatrixCSR() override = default;

    // 接口实现
    bool isSparse() const override { return true; }
    size_t rows() const override { return numRows; }
    size_t cols() const override { return numCols; }
    double density() const override;
    std::string type() const override { return "SparseMatrixCSR"; }
    MatrixBase* clone() const override { return new SparseMatrixCSR(*this); }

    // 获取 CSR 各部分数据
    const std::vector<double>& getValues() const { return values; }
    const std::vector<int>& getColIndices() const { return colIndices; }
    const std::vector<int>& getRowPtr() const { return rowPtr; }

    // 打印矩阵
    void print(int maxRows = 5) const;
};

#endif //SPARSEMATRIXCSR_HPP
