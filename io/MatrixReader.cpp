//
// Created by hexy on 25-6-15.
//
#include "MatrixReader.hpp"
#include "../matrix/SparseMatrixCSR.hpp"
#include "../matrix/SparseMatrixCSC.hpp"
#include "../matrix/DenseMatrix.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

MatrixBase* MatrixReader::readMatrix(const std::string& filePath, const std::string& format) {
    if (format == "csr") {
        return readCSR(filePath);
    } else if (format == "csc") {
        return readCSC(filePath);
    } else if (format == "csv") {
        return readCSV(filePath);
    } else {
        throw std::invalid_argument("不支持的格式: " + format);
    }
}

MatrixBase* MatrixReader::readCSR(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw std::runtime_error("打开文件失败: " + filePath);
    }

    int numRows, numCols, nnz;
    fin >> numRows >> numCols >> nnz;

    std::vector<double> values(nnz);
    std::vector<int> colIndices(nnz);
    std::vector<int> rowPtr(numRows + 1);

    for (int i = 0; i <= numRows; ++i) fin >> rowPtr[i];
    for (int i = 0; i < nnz; ++i) fin >> colIndices[i];
    for (int i = 0; i < nnz; ++i) fin >> values[i];

    return new SparseMatrixCSR(numRows, numCols, values, colIndices, rowPtr);
}

MatrixBase* MatrixReader::readCSC(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw std::runtime_error("打开文件失败: " + filePath);
    }

    int numRows, numCols, nnz;
    fin >> numRows >> numCols >> nnz;

    std::vector<double> values(nnz);
    std::vector<int> rowIndices(nnz);
    std::vector<int> colPtr(numCols + 1);

    for (int i = 0; i <= numCols; ++i) fin >> colPtr[i];
    for (int i = 0; i < nnz; ++i) fin >> rowIndices[i];
    for (int i = 0; i < nnz; ++i) fin >> values[i];

    return new SparseMatrixCSC(numRows, numCols, values, rowIndices, colPtr);
}

MatrixBase* MatrixReader::readCSV(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw std::runtime_error("打开文件失败: " + filePath);
    }

    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(fin, line)) {
        std::istringstream ss(line);
        std::vector<double> row;
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (token.empty()) continue;
            row.push_back(std::stod(token));
        }
        if (!row.empty()) data.push_back(row);
    }

    size_t rows = data.size();
    size_t cols = data[0].size();

    std::vector<double> flatData;
    for (const auto& row : data) {
        flatData.insert(flatData.end(), row.begin(), row.end());
    }

    return new DenseMatrix(rows, cols, flatData);
}