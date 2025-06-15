//
// Created by hexy on 25-6-15.
//
#include "../matrix/MatrixBase.hpp"
#include "RowPartitioner.hpp"
#include <vector>

std::vector<std::pair<int, int>> RowPartitioner::partition(int worldSize, const MatrixBase& matrix) const {
    size_t totalRows = matrix.rows();
    size_t rowsPerProcess = totalRows / worldSize;
    size_t remainder = totalRows % worldSize;

    std::vector<std::pair<int, int>> ranges;
    int offset = 0;

    for (int i = 0; i < worldSize; ++i) {
        int rowCount = rowsPerProcess + (i < remainder ? 1 : 0);
        int start = offset;
        int end = offset + rowCount;
        ranges.emplace_back(start, end);
        offset += rowCount;
    }

    return ranges;
}