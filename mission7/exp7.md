---
permalink: /mission7/exp7.html
layout: default
title: contents of mission 7
---

# 实验七
## 题目
综合实验
## 需求分析
1. 输入形式：输入数字表示执行的操作名，各种操作还需要输入字符串，数字等。 \
   输入值的范围：字符、数字
2. 输出的形式：输出在界面上以及txt文件中。凹入表打印平衡树在屏幕上。
3. 功能：

    **采编入库**：新购入一种书，经分类和确定书号之后登记到图书帐目中去。如果这种书在帐中已有，则只将该书的总库存量增加。

    **借阅**：如果一种书的现存量大于零，则借出一本，登记借阅者的图书证号和归还期限。

    **归还**：注销对借阅者的登记，改变该书的现存量（如果借阅者归还所有的书，则注销该借阅者的信息）。
    
    **注销**：某种书已无保留价值，将它从图书帐目中注销。
    
    **显示**：实现图书管理的显示操作：每次插入或删除平衡二叉树的一个结点之后，更新平衡二叉树的显示。


## 代码
[cpp](./Project1/1.cpp)