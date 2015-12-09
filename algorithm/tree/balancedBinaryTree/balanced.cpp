#include "balanced.h"
#include <stack>
#include <iostream>

pbalaTree createBalanceNode(ElemType data)
{
    pbalaTree node = new balaTree;
    if (node == nullptr)
    {
        return nullptr;
    }
    node->data = data;
    node->uHeight = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

pbalaTree insertBalanceTree(pbalaTree tree, ElemType data)
{
    if (nullptr == tree)
    {
        tree = createBalanceNode(data);
        tree->uHeight = 0;
        return tree;
    }

    if (data < tree->data)
    {
        // 左子树
        tree->left = insertBalanceTree(tree->left, data);
        // 左右树差值
        if (subTree(tree->left,tree->right) == 2)
        {
            if (data < tree->left->data)
            {
                tree = RoateLL(tree);
            }
            else
            {
                tree = RoateLR(tree);
            }
        }
    }
    else if(data > tree->data)
    {
        // 右子树
        tree->right = insertBalanceTree(tree->right, data);
        if (subTree(tree->right, tree->left) == 2)
        {
            if (data > tree->right->data)
            {
                tree = RoateRR(tree);
            }
            else
            {
                tree = RoateRL(tree);
            }
        }
    }
    else
    {
        return tree;
    }
    tree->uHeight = Max(getHeight(tree->left), getHeight(tree->right)) + 1;
    return tree;
}

pbalaTree deleteNodeRight(pbalaNode node, ElemType data)
{
    if (nullptr == node)
    {
        return node;
    }

    if (data == node->data)
    {
        // 找到删除的节点
        if (nullptr != node->right && nullptr != node->left)
        {
            pbalaNode head = node;
            pbalaNode tmp = node->right;
            while (nullptr != (tmp->left))
            {
                head = tmp;
                tmp = tmp->left;
            }
            node->data = tmp->data;
            head->right = deleteNodeRight(head->right, node->data);
        }
        else
        {
            pbalaNode tmp = node;
            node = ((nullptr == node->left)? node->right : node->left);
            delete tmp;
            tmp = nullptr;
            if (nullptr == node)
            {
                return node;
            }
        }
    }
    else if (data > node->data)
    {
        //
        node->right = deleteNodeRight(node->right, data);
    }
    else
    {
        //
        node->left = deleteNodeRight(node->left, data);
    }
    node->uHeight = Max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

pbalaTree deleteNodeLeft(pbalaNode node, ElemType data)
{
    if (nullptr == node)
    {
        return node;
    }

    if (data == node->data)
    {
        if (nullptr != node->right && nullptr != node->left)
        {
            pbalaNode head = node;
            pbalaNode tmp = node->left;
            while (nullptr != (tmp->right))
            {
                head = tmp;
                tmp = tmp->right;
            }
            node->data = tmp->data;
            head->right = deleteNodeLeft(head->left, node->data);
        }
        else
        {
        }
    }
    else if(data < node->data)
    {
        node->left = deleteNodeLeft(node->left, data);
    }
    else
    {
        node->right = deleteNodeLeft(node->right, data);
    }
    node->uHeight = Max(getHeight(node->left),getHeight(node->right)) + 1;
    return node;
}

void deleteAll(pbalaTree &tree)
{
    if (nullptr == tree)
    {
        return;
    }
    if (nullptr != tree->left)
    {
        deleteAll(tree->left);
    }
    if (nullptr != tree->right)
    {
        deleteAll(tree->right);
    }
    delete tree;
    tree = nullptr;
    return;
    return;
}

pbalaTree RoateLL(pbalaTree tree)
{
    pbalaNode top = tree->left;
    tree->left = top->right;
    top->right = tree;
    tree->uHeight = Max(getHeight(tree->left), getHeight(tree->right)) + 1;
    top->uHeight = Max(getHeight(top->left), getHeight(top->right)) + 1;
    return top;
}
pbalaTree RoateLR(pbalaTree tree)
{
    tree->left = RoateRR(tree->left);
    return RoateLL(tree);
}
pbalaTree RoateRR(pbalaTree tree)
{
    pbalaNode top = tree->right;
    tree->right = top->left;
    top->left = tree;
    tree->uHeight = Max(getHeight(tree->left), getHeight(tree->right)) + 1;
    top->uHeight - Max(getHeight(top->left), getHeight(top->right)) + 1;
    return top;
}
pbalaTree RoateRL(pbalaTree tree)
{
    tree->right = RoateLL(tree->right);
    return RoateRR(tree);
}

using std::cout;
using std::endl;
void DLR(pbalaTree tree)
{
    if (nullptr != tree)
    {
        cout << tree->data << " " << tree->uHeight << " ";
        DLR(tree->left);
        DLR(tree->right);
        return;
    }
}
void LRD(pbalaTree tree)
{
    if (nullptr != tree)
    {
        LRD(tree->left);
        LRD(tree->right);
        cout << tree->data << " " << tree->uHeight << " ";
        return;
    }
}

void LDR(pbalaTree tree)
{
    if (nullptr != tree)
    {
        LDR(tree->left);
        cout << tree->data << " " << tree->uHeight << " ";
        LDR(tree->right);
        return;
    }
}

pbalaNode searchData(pbalaTree tree, ElemType data)
{
    pbalaNode node = tree;
    while (nullptr != node)
    {
        if (node->data == data)
        {
            // copy
            pbalaNode tp = new balaNode;
            tp->data = node->data;
            tp->left = node->left;
            tp->right - node->right;
            return tp;
        }
        if (node->data > data)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return nullptr;
}

