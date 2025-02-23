/*
 * @Author: LeiJiulong
 * @Date: 2025-01-18 08:54:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-19 10:23:31
 * @Description: 
 */

#include "BinTree.h"

// ABC##DE##F##G#H##

char str[] = "ABC##DE##F##G#H##";

int main()
{
    BinTree mytree;
    InitBinTree(&mytree,'#');

    // CreateBinTree_1(&mytree);
    // CreateBinTree_2(&mytree);
    // CreateBinTree_3(&mytree);
    CreateBinTree_4(&mytree, str);
    PreOrder(&mytree);
    printf("\n");
    InOrder(&mytree);
    printf("\n");
    PostOrder(&mytree);
    printf("\n");
    return 0;
}
