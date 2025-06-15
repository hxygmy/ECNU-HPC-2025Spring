//
// Created by hexy on 25-6-15.
//
#include "MatrixWriter.hpp"
#include <fstream>
#include <stdexcept>
#include "../matrix/SparseMatrixCSC.hpp"
#include "../matrix/SparseMatrixCSR.hpp"

void MatrixWriter::writeMatrix(const MatrixBase* matrix, const std::string& filePath, const std::string& format) {
    if (format == "csr") {
        writeCSR(matrix, filePath);
    } else if (format == "csc") {
        writeCSC(matrix, filePath);
    } else if (format == "csv") {
        writeCSV(matrix, filePath);
    } else {
        throw std::invalid_argument("Unsupported output format: " + format);
    }
}

void MatrixWriter::writeCSR(const MatrixBase* matrix, const std::string& filePath) {
    if (matrix->type() != "SparseMatrixCSR") {
        throw std::runtime_error("Cannot write CSR format from non-CSR matrix.");
    }

    const auto* csr = dynamic_cast<const SparseMatrixCSR*>(matrix);
    std::ofstream fout(filePath);
    if (!fout.is_open()) {
        throw std::runtime_error("Failed to open file for writing CSR: " + filePath);
    }

    fout << csr->rows() << " " << csr->cols() << " " << csr->getValues().size() << "\n";

    const auto& rowPtr = csr->getRowPtr();
    const auto& colIdx = csr->getColIndices();
    const auto& values = csr->getValues();

    for (size_t i = 0; i < rowPtr.size(); ++i) fout << rowPtr[i] << " ";
    fout << "\n";

    for (size_t i = 0; i < colIdx.size(); ++i) fout << colIdx[i] << " ";
    fout << "\n";

    for (size_t i = 0; i < values.size(); ++i) fout << values[i] << " ";
    fout << "\n";
}

void MatrixWriter::writeCSC(const MatrixBase* matrix, const std::string& filePath) {
    if (matrix->type() != "SparseMatrixCSC") {
        throw std::runtime_error("Cannot write CSC format from non-CSC matrix.");
    }

    const auto* csc = dynamic_cast<const SparseMatrixCSC*>(matrix);
    std::ofstream fout(filePath);
    if (!fout.is_open()) {
        throw std::runtime_error("Failed to open file for writing CSC: " + filePath);
    }

    fout << csc->rows() << " " << csc->cols() << " " << csc->getValues().size() << "\n";

    const auto& colPtr = csc->getColPtr();
    const auto& rowIdx = csc->getRowIndices();
    const auto& values = csc->getValues();

    for (size_t i = 0; i < colPtr.size(); ++i) fout << colPtr[i] << " ";
    fout << "\n";

    for (size_t i = 0; i < rowIdx.size(); ++i) fout << rowIdx[i] << " ";
    fout << "\n";

    for (size_t i = 0; i < values.size(); ++i) fout << values[i] << " ";
    fout << "\n";
}

void MatrixWriter::writeCSV(const MatrixBase* matrix, const std::string& filePath) {
    std::ofstream fout(filePath);
    if (!fout.is_open()) {
        throw std::runtime_error("Failed to open file for writing CSV: " + filePath);
    }

    size_t rows = matrix->rows();
    size_t cols = matrix->cols();

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            fout << matrix->at(i, j);
            if (j != cols - 1) fout << ",";
        }
        fout << "\n";
    }
}