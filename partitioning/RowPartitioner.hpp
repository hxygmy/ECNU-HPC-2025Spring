//
// Created by hexy on 25-6-15.
//

#ifndef ROWPARTITIONER_HPP
#define ROWPARTITIONER_HPP

#include "PartitionStrategy.hpp"

class RowPartitioner : public PartitionStrategy {
public:
    RowPartitioner() = default;
    ~RowPartitioner() override = default;

    // 行分块逻辑：返回每个进程应处理的 (start_row, end_row)
    std::vector<std::pair<int, int>> partition(int worldSize, const MatrixBase& matrix) const override;

    std::string type() const override { return "RowPartitioner"; }
    PartitionStrategy* clone() const override { return new RowPartitioner(*this); }
};

#endif // ROWPARTITIONER_HPP