#pragma once

namespace hw {

struct AvlNode
{
    AvlNode() = default;
    AvlNode(int v)
      : value(v)
      , height(1)
    {}

    int      value   = 0;
    int      height  = -1;
    int      balance = 0;
    AvlNode* left    = nullptr;
    AvlNode* right   = nullptr;
};

class AvlTree
{
public:
    AvlTree() = default;
    ~AvlTree();

    void insert(int value);
    void remove(int value);

    bool empty() const;
    int  height() const;
    int  balance() const;

    AvlNode* root() const { return root_; }

private:
    AvlNode* root_ = nullptr;

    void smallLeftRotation();
    void smallRightRotation();
    void bigLeftRotation();
    void bigRightRotation();
    void rebalance(AvlNode* n);

    void     destroyTree(AvlNode* n);
    AvlNode* insertNodeAt(AvlNode* p, AvlNode* n);
};

} // namespace hw
