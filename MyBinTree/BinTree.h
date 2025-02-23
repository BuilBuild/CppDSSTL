/*
 * @Author: LeiJiulong
 * @Date: 2025-01-18 08:53:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-19 10:34:29
 * @Description: 
 */
#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#include <queue>



#define ElemType char

using namespace std;
using QueueChar = queue<ElemType>;

typedef struct  BinTreeNode
{
    ElemType data;
    struct BinTreeNode *leftChild;
    struct BinTreeNode *rightChild;
} BinTreeNode;

typedef struct BinTree
{
    BinTreeNode *root;
    ElemType refvalue; // stop flag
} BinTree;

/**
 * @brief 初始化二叉树
 * @param ref 结束标记
 */
void InitBinTree(BinTree*, ElemType ref);

void CreateBinTree_1(BinTree *);
void CreateBinTree_1(BinTree *bt, BinTreeNode **t);

void CreateBinTree_2(BinTree *);
void CreateBinTree_2(BinTree *, BinTreeNode *&);

void CreateBinTree_3(BinTree *);
BinTreeNode *CreateBinTree_3_(BinTree *);

void CreateBinTree_4(BinTree *, char *);
void CreateBinTree_4(BinTree *, BinTreeNode *&, char *&);

// 前序遍历
void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);
// 中序遍历
void InOrder(BinTree *bt);
void InOrder(BinTreeNode *t);
// 后序遍历
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);
// 层次遍历
void LevelOrder(BinTree *bt);
void LevelOrder(BinTreeNode *t);


