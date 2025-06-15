//
// Created by hexy on 25-6-14.
//

#ifndef PARTITIONSTRATEGY_HPP
#define PARTITIONSTRATEGY_HPP
#include <vector>
#include <string>

class MatrixBase;

class PartitionStrategy {
public:
    virtual ~PartitionStrategy() = default;

    // 将矩阵划分为若干子块，返回每个进程负责的起始和结束索引
    virtual std::vector<std::pair<int, int>> partition(int worldSize, const MatrixBase& matrix) const = 0;

    // 获取分区类型名称
    virtual std::string type() const = 0;

    // 多态拷贝
    virtual PartitionStrategy* clone() const = 0;
};
#endif //PARTITIONSTRATEGY_HPP
