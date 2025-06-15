//
// Created by hexy on 25-6-15.
//
#ifndef MATRIXWRITER_HPP
#define MATRIXWRITER_HPP

#include "../matrix/MatrixBase.hpp"

class MatrixWriter {
public:
    // 写出矩阵到文件
    static void writeMatrix(const MatrixBase* matrix, const std::string& filePath, const std::string& format);

private:
    static void writeCSR(const MatrixBase* matrix, const std::string& filePath);
    static void writeCSC(const MatrixBase* matrix, const std::string& filePath);
    static void writeCSV(const MatrixBase* matrix, const std::string& filePath);
};

#endif // MATRIXWRITER_HPP
