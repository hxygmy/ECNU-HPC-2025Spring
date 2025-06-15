//
// Created by hexy on 25-6-15.
//
#include "../matrix/MatrixBase.hpp"
#include "BlockPartitioner.hpp"
#include <cmath>
#include <stdexcept>

std::vector<std::pair<int, int>> BlockPartitioner::partition(int worldSize, const MatrixBase& matrix) const {
    size_t totalRows = matrix.rows();
    size_t totalCols = matrix.cols();

    // 简化：假设 worldSize 是平方数，并平均划分成 sqrt(worldSize) x sqrt(worldSize) 的块
    int gridSize = static_cast<int>(std::sqrt(worldSize));
    if (gridSize * gridSize != worldSize) {
        throw std::invalid_argument("World size must be a perfect square for block partitioning.");
    }

    std::vector<std::pair<int, int>> ranges;
    size_t rowsPerBlock = totalRows / gridSize;
    size_t colsPerBlock = totalCols / gridSize;

    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            int startRow = r * rowsPerBlock;
            int endRow = (r == gridSize - 1) ? totalRows : startRow + rowsPerBlock;

            int startCol = c * colsPerBlock;
            int endCol = (c == gridSize - 1) ? totalCols : startCol + colsPerBlock;

            ranges.emplace_back(std::make_pair(startRow, endRow));
            ranges.emplace_back(std::make_pair(startCol, endCol));
        }
    }

    return ranges;
}
