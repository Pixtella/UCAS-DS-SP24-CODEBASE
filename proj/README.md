### 课程大作业

#### 马踏棋盘的神经网络解法

定义式请见slides，主要思路是用神经网络表示图，神经网络的状态表示图上的路径，收敛的状态（不再演化的状态）表示哈密尔顿回路

注意：神经网络可能不收敛；收敛得到的路径可能为多个分立的闭环（不是解）；求解失败则重新初始化神经网络然后再次运行

**chess.py**

requirements: python3 pygame matplotlib networkx numpy

求解+图形界面演示，运行速度较慢

```shell
python3 chess.py
```

**nn.cpp**

求解+命令行输出，运行速度较快，适用更大棋盘

#### AVL Tree

**avl-tree.c**

AVL树的实现，包括查找，插入，删除等操作，命令行演示