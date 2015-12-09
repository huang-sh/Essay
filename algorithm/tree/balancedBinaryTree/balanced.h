#ifndef BALANCED_H_
#define BALANCED_H_

#include <stdint.h>
#include <math.h>

#define isNullReturn(point,returnVal) \
    if (nullptr == (point)) { return (returnVal); }

#define getHeight(pnode) \
    ( ((pnode) == nullptr) ? -1 : pnode->uHeight)

#define Max(left, right) \
    ( ((left) > (right)) ? left : right)

#define subTree(point1,point2)\
    abs(getHeight(point1) - getHeight(point2))

#define abs_32(num)\
    ((num ^ (num >> 31)) - (n >> 31))

#define subNum(num1, num2) \
    (num1 - num2)

enum returnType
{
    error = 100,
    isok = 200
};

typedef uint64_t ElemType;

typedef struct balancedTree
{
    struct balancedTree *left;
    struct balancedTree *right;
    ElemType data;
    int32_t uHeight;
} balaTree, balaNode, *pbalaTree, *pbalaNode;

//uint64_t random
pbalaTree createBalanceNode(ElemType data);
pbalaTree insertBalanceTree(pbalaTree tree, ElemType data);
pbalaTree deleteNodeRight(pbalaNode node, ElemType data);
pbalaTree deleteNodeLeft(pbalaNode node, ElemType data);
void deleteAll(pbalaTree &tree);
pbalaTree RoateLL(pbalaTree tree);
pbalaTree RoateLR(pbalaTree tree);
pbalaTree RoateRR(pbalaTree tree);
pbalaTree RoateRL(pbalaTree tree);
/**
 * 这是先序遍历树
 **/
void DLR(pbalaTree tree);
/**
 * 这是后序遍历树
 **/
void LRD(pbalaTree tree);
/**
 * 这是中序遍历树
 **/
void LDR(pbalaTree tree);

/**
 * 搜索
 **/
pbalaNode searchData(pbalaNode node, ElemType data);

#endif // BALANCED_H_
