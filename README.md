## 分布式矩阵计算：稀疏与稠密矩阵乘法运算 
实现一个支持大规模稀疏/稠密矩阵乘法的分布式计算程序，使用c++和openmpi，运行于多节点 HPC 集群，
任务包括：
- 支持矩阵分块和任务划分（按行或按块）
- 稀疏矩阵支持 CSR/CSC 格式，高效乘法
- 结果可用于后续线性代数计算（求 PageRank）

### 架构设计

```
MatrixMultiplication/
├── main.cpp                    // 主程序入口
├── matrix/                     // 矩阵抽象与实现
│   ├── MatrixBase.hpp          // 抽象接口：判断稀疏/稠密等
│   ├── DenseMatrix.hpp         // 稠密矩阵类
│   ├── SparseMatrixCSR.hpp     // CSR 格式稀疏矩阵类
│   ├── SparseMatrixCSC.hpp     // CSC 格式稀疏矩阵类
│   └── MatrixFactory.hpp       // 工厂模式创建矩阵对象
├── partitioning/               // 分块和任务划分模块
│   ├── BlockPartitioner.hpp    // 块分块策略
│   ├── RowPartitioner.hpp      // 行分块策略
│   └── PartitionStrategy.hpp   // 分区策略基类
├── multiplication/             // 矩阵乘法
│   ├── MatMulDispatcher.hpp    // 分发器
│   ├── DenseDenseMatMul.hpp    // 稠密×稠密乘法
│   ├── DenseSparseMatMul.hpp   // 稠密×稀疏乘法
│   └── SparseSparseMatMul.hpp  // 稀疏×稀疏乘法
├── pagerank/                   // PageRank 测试
│   ├── PageRankSolver.hpp      
└── io/                         // 文件读写模块
    ├── MatrixReader.hpp        // 读取矩阵（CSR/CSC/文本）
    └── MatrixWriter.hpp        // 写出结果矩阵
```