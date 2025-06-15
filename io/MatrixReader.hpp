//
// Created by hexy on 25-6-15.
//

#ifndef MATRIXREADER_HPP
#define MATRIXREADER_HPP

#include "../matrix/MatrixBase.hpp"

class MatrixReader {
public:
    // 根据输入类型读取矩阵
    static MatrixBase* readMatrix(const std::string& filePath, const std::string& format);

private:
    // 具体实现方法
    static MatrixBase* readCSR(const std::string& filePath);
    static MatrixBase* readCSC(const std::string& filePath);
    static MatrixBase* readCSV(const std::string& filePath);
};

#endif // MATRIXREADER_HPP
