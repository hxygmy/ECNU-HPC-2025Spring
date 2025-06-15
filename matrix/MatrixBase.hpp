//
// Created by hexy on 25-6-14.
//
#ifndef MATRIXBASE_HPP
#define MATRIXBASE_HPP

#include <string>

/*
矩阵的基类, 判断是否为稀疏矩阵, 获取行数与列数, 元素密度

TODO : 建立一个 MatrixFactory, 可以从 DenseMatrix 格式的输入智能决定创建什么格式的 Matrix
*/
class MatrixBase {
public:
    virtual ~MatrixBase() = default;

    virtual bool isSparse() const = 0;

    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    virtual double density() const = 0;

    // for debug
    virtual std::string type() const = 0;
    // 深拷贝函数
    virtual MatrixBase* clone() const = 0;
};

#endif // MATRIXBASE_HPP