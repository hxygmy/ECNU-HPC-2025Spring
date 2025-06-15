//
// Created by hexy on 25-6-14.
//

#ifndef BLOCKPARTITIONER_HPP
#define BLOCKPARTITIONER_HPP

#include "PartitionStrategy.hpp"

class BlockPartitioner : public PartitionStrategy {
public:
    BlockPartitioner() = default;
    ~BlockPartitioner() override = default;

    // 块分块逻辑：返回每个进程应处理的 (start_row, end_row) 和 (start_col, end_col)
    std::vector<std::pair<int, int>> partition(int worldSize, const MatrixBase& matrix) const override;

    std::string type() const override { return "BlockPartitioner"; }
    PartitionStrategy* clone() const override { return new BlockPartitioner(*this); }
};

#endif //BLOCKPARTITIONER_HPP
