/*
 * @Author: LeiJiulong
 * @Date: 2025-01-18 08:59:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-19 10:23:16
 * @Description: 
 */

#include "BinTree.h"


void InitBinTree(BinTree *treePtr,  ElemType ref)
{
    treePtr->root = NULL;
    treePtr->refvalue = ref;
}

void CreateBinTree_1(BinTree *bt)
{
    CreateBinTree_1(bt, &(bt->root));
}

void CreateBinTree_1(BinTree *bt, BinTreeNode **t)
{
    ElemType Item;
    int rs = scanf("%c", &Item);
    if(Item == bt->refvalue)
        *t = NULL;
    else
    {
        *t= (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(*t != NULL);
        (*t)->data = Item;
        CreateBinTree_1(bt, &((*t)->leftChild));
        CreateBinTree_1(bt, &((*t)->rightChild));
    }
}

void CreateBinTree_2(BinTree *bt)
{
    CreateBinTree_2(bt, bt->root);
}

void CreateBinTree_2(BinTree *bt, BinTreeNode *&t)
{
    ElemType Item;
    int flag = scanf("%c", &Item);
    if(Item == bt->refvalue)
        t = NULL;
    else
    {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t!=NULL);
        t->data = Item;
        CreateBinTree_2(bt, t->leftChild);
        CreateBinTree_2(bt, t->rightChild);
    }
}

void CreateBinTree_3(BinTree *bt)
{
    bt->root = CreateBinTree_3_(bt);
}

BinTreeNode *CreateBinTree_3_(BinTree *bt)
{
    ElemType Item;
    int flag = scanf("%c", &Item);
    if(Item == bt->refvalue)
        return NULL;
    else
    {
        BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t->data = Item;
        t->leftChild = CreateBinTree_3_(bt);
        t->rightChild = CreateBinTree_3_(bt);
        return t;
    }
}

void CreateBinTree_4(BinTree *bt, char *str)
{
    CreateBinTree_4(bt, bt->root, str);
}

void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str)
{
    if(*str == bt->refvalue)
        t = NULL;
    else
    {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        assert(t != NULL);
        t ->data = *str;
        CreateBinTree_4(bt, t->leftChild, ++str);
        CreateBinTree_4(bt, t->rightChild, ++str);
    }
}

void PreOrder(BinTree *bt)
{
    PreOrder(bt->root);
}

void PreOrder(BinTreeNode *t)
{
    if(t!=NULL)
    {
        printf("%c ", t->data);
        PreOrder(t->leftChild);
        PreOrder(t->rightChild);
    }
}

void InOrder(BinTree *bt)
{
    InOrder(bt->root);
}

void InOrder(BinTreeNode *t)
{
    if(t!=NULL)
    {
        InOrder(t->leftChild);
        printf("%c ", t->data);
        InOrder(t->rightChild);
    }
}

void PostOrder(BinTree *bt)
{
    PostOrder(bt->root);
}

void PostOrder(BinTreeNode *t)
{
    if(t!=NULL)
    {
        PostOrder(t->leftChild);
        PostOrder(t->rightChild);
        printf("%c ", t->data);
    }
}

void LevelOrder(BinTree *bt)
{
    LevelOrder(bt->root);
}

void LevelOrder(BinTreeNode *t)
{
    
}
