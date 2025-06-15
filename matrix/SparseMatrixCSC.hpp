//
// Created by hexy on 25-6-14.
//

/*

CSC格式通过三个数组来存储稀疏矩阵的数据：

values：存储矩阵中的所有非零元素。
rowIndices：存储每个非零元素对应的行索引。
colPtr：指示每列开始非零元素的位置。在这个数组中，元素 colPtr[j] 表示第 j 列的第一个非零元素在 values 数组中的位置。

 */
#ifndef SPARSEMATRIXCSC_HPP
#define SPARSEMATRIXCSC_HPP

#include "MatrixBase.hpp"
#include <vector>

class SparseMatrixCSC : public MatrixBase {
private:
    size_t numRows;
    size_t numCols;
    std::vector<double> values;
    std::vector<int> rowIndices;
    std::vector<int> colPtr;

public:
    // 构造函数
    SparseMatrixCSC(size_t rows, size_t cols,
                    const std::vector<double>& vals,
                    const std::vector<int>& rowIdx,
                    const std::vector<int>& colP);

    // 拷贝构造
    SparseMatrixCSC(const SparseMatrixCSC& other);
    SparseMatrixCSC& operator=(const SparseMatrixCSC& other);
    ~SparseMatrixCSC() override = default;

    // 接口实现
    bool isSparse() const override { return true; }
    size_t rows() const override { return numRows; }
    size_t cols() const override { return numCols; }
    double density() const override;
    std::string type() const override { return "SparseMatrixCSC"; }
    MatrixBase* clone() const override { return new SparseMatrixCSC(*this); }

    // 获取 CSC 各部分数据
    const std::vector<double>& getValues() const { return values; }
    const std::vector<int>& getRowIndices() const { return rowIndices; }
    const std::vector<int>& getColPtr() const { return colPtr; }

    // 打印矩阵（调试用）
    void print(int maxCols = 5) const;
};
#endif //SPARSEMATRIXCSC_HPP
